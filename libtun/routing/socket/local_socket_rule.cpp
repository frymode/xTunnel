#include "stdafx.h"
#include "local_socket_rule.h"

#include "socket_acceptor.h"
#include "../../net/io_service_pool.h"

namespace xTunnel
{
    LocalSocketRule::~LocalSocketRule()
    {
    }

    void LocalSocketRule::Load(const ConfigProperties& cfg)
    {
        port = cfg.get<int>("port");
    }

    ConfigProperties LocalSocketRule::Save() const
    {
        ConfigProperties cfg =  EndpointRule::Save();
        cfg.add("port", port);

        return cfg;
    }

    AcceptorPtr LocalSocketRule::CreateAcceptor(const Acceptor::Handler& handler)
    {
        auto rule_ptr = static_pointer_cast<LocalSocketRule>(shared_from_this());
        auto acceptor = make_shared<SocketAcceptor>(rule_ptr);
        acceptor->Start(handler);
        return acceptor;
    }
}