#include "stdafx.h"
#include "socket_connector.h"

#include "socket_endpoint.h"
#include "net/io_service_pool.h"

namespace xTunnel
{
    SocketConnector::SocketConnector(const RemoteSocketRulePtr& rule)
        :_rule(rule)
    {
        _socket = make_shared<Socket>(io_service_pool::get_io_service());
    }

    SocketConnector::~SocketConnector()
    {
        if (_socket)
        {
            _socket->shutdown(Socket::shutdown_both);
        }
    }

    void SocketConnector::BeginConnect()
    {
        tcp::resolver::query query(_rule->host, to_string(_rule->port));
        tcp::resolver resolver(_socket->get_io_service());
        auto endpoint_iterator = resolver.resolve(query);

        LOG_DEBUG(logs::net, "Connecting to " << _rule->description());
        boost::asio::async_connect(*_socket, endpoint_iterator,
            bind(&SocketConnector::HandleConnect, shared_from_this(), placeholders::_1));
    }

    void SocketConnector::HandleConnect(weak_ptr<SocketConnector> self, const ErrorCode& error)
    {
        auto connector = self.lock();
        if (connector)
        {
            connector->EndConnect(error);
        }
        else
        {
            LOG_DEBUG(logs::net, "Connector instance destroyed while connecting");
        }
    }

    void SocketConnector::EndConnect(const ErrorCode& error)
    {
        if (error)
        {
            LOG_INFO(logs::net, "Connect to " << _rule->description() << " failed: " << error.message());
            _socket.reset();
            OnConnect(ConnectResult::FromException(SystemError()));
            return;
        }

        LOG_DEBUG(logs::net, "Connected to " << _rule->description());
        _socket->set_option(tcp::no_delay(true));
        _socket->set_option(tcp::socket::keep_alive(true));

        ConnectResult res(make_shared<SocketEndpoint>(_rule, _socket));
        OnConnect(res);
    }
}