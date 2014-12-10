#include "stdafx.h"
#include "socket_endpoint.h"

namespace xTunnel
{
	SocketEndpoint::SocketEndpoint(const EndpointRulePtr& rule, const SocketPtr& socket)
		: Endpoint(rule),
          _socket(socket),
          _sending(false)
	{
        if (_socket->is_open())
		{
			SetState(kActive);
		}
	}

    SocketEndpoint::~SocketEndpoint()
    {
    }

    void SocketEndpoint::Close()
    {
        _sending = false;
        _socket->shutdown(Socket::shutdown_both);
    }

    void SocketEndpoint::BeginReceive(const ReceiveHandler& handler)
    {
        _handler = handler;
        BeginReceive();
    }

    void SocketEndpoint::BeginReceive()
    {
        int size = buf_policy_.GetSize();
        if (buf_.size != size)
        {
            buf_.Reset(size);
        }

        _socket->async_read_some(boost::asio::buffer(buf_.data, buf_.size),
            bind(&SocketEndpoint::HandleReceive, this, placeholders::_1, placeholders::_2));
    }

    void SocketEndpoint::HandleReceive(const ErrorCode& error, const size_t& bytes_received)
    {
        if (error)
        {
            Close();
            return;
        }

        AddReceived(bytes_received);
        buf_policy_.SetUsedSize(bytes_received);
        BeginReceive();
    }

    void SocketEndpoint::Send(const char* buf, int size)
    {
        if (IsActive() && !_sending)
        {
            _sending = true;
            _out_buf.Reset(buf, size);
            _socket->async_send(boost::asio::buffer(_out_buf.data, _out_buf.size),
                                bind(&SocketEndpoint::HandleSend, this, placeholders::_1, placeholders::_2));
        }
        else
        {
            UniqueLock lock(_mutex);
            _out_queue.Append(buf, size);
        }
    }

    void SocketEndpoint::HandleSend(const ErrorCode& error, const size_t& bytes_sent)
    {
        if (error)
        {
            Close();
        }

        AddSent(bytes_sent);
        SendQueue();
    }

    bool SocketEndpoint::SendQueue()
    {
        UniqueLock lock(_mutex);
        if (_out_queue.size == 0)
        {
            _sending = false;
            return false;
        }

        _out_buf.Reset();
        _out_buf.Swap(_out_queue);
        _socket->async_send(boost::asio::buffer(_out_buf.data, _out_buf.size),
                            bind(&SocketEndpoint::HandleSend, this, placeholders::_1, placeholders::_2));
        return true;
    }
}