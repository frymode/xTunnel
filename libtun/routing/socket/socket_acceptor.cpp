#include "stdafx.h"
#include "socket_acceptor.h"

#include "socket_endpoint.h"
#include "net/io_service_pool.h"

namespace xTunnel
{
    SocketAcceptor::SocketAcceptor(const LocalSocketRulePtr& rule)
        : _rule(rule),
          _impl(io_service_pool::get_io_service(), tcp::endpoint(tcp::v4(), rule->port))
    {
    }

    SocketAcceptor::~SocketAcceptor()
    {
        LOG_INFO(logs::net, "Stopping socket acceptor: " << "...");
        _impl.close();
    }

    void SocketAcceptor::BeginAccept()
    {
        LOG_INFO(logs::net, "Begin socket accept: " << "...");
        auto socket = make_shared<Socket>(_impl.get_io_service());

        _impl.async_accept(*socket, bind(&SocketAcceptor::HandleAccept, shared_from_this(), socket, placeholders::_1));
    }

    void SocketAcceptor::HandleAccept(weak_ptr<SocketAcceptor> self, SocketPtr socket, const ErrorCode& error)
    {
        auto acceptor = self.lock();
        if (acceptor)
        {
            acceptor->EndAccept(socket, error);
        }
    }

    void SocketAcceptor::EndAccept(const SocketPtr& socket, const ErrorCode& error)
    {
		if (error)
		{
            LOG_INFO(logs::net, "Accept at " << _rule->description() << " failed: " << error.message());
            OnAccept(AcceptResult::FromException(SystemError()));
            return;
		}

        LOG_INFO(logs::net, "Incoming connection at: " << "..." << " from " << "...");
        socket->set_option(tcp::no_delay(true));
        socket->set_option(tcp::socket::keep_alive(true));

        AcceptResult res(make_shared<SocketEndpoint>(_rule, socket));
        OnAccept(res);
        BeginAccept();
    }
}