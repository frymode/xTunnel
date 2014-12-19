#include "stdafx.h"
#include "remote_socket_rule.h"

#include "socket_connector.h"
#include "../../net/io_service_pool.h"

namespace xTunnel
{
    RemoteSocketRule::RemoteSocketRule()
    {
        port = 0;
    }

    RemoteSocketRule::~RemoteSocketRule()
    {
    }

    void RemoteSocketRule::Load(const ConfigProperties& cfg)
    {
        host = cfg.get<string>("host");
        port = cfg.get<int>("port");
    }

    ConfigProperties RemoteSocketRule::Save() const
    {
        ConfigProperties cfg = EndpointRule::Save();
        cfg.add("host", host);
        cfg.add("port", port);

        return cfg;
    }

    ConnectorPtr RemoteSocketRule::CreateConnector(const Connector::Handler& handler)
    {
        auto rule_ptr = static_pointer_cast<RemoteSocketRule>(shared_from_this());
        auto connector = make_shared<SocketConnector>(rule_ptr);
        connector->Start(handler);
        return connector;
    }
}