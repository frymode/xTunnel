#include "stdafx.h"
#include "socket_routing_rule.h"

#include "socket_session.h"

namespace xTunnel
{
    SocketRoutingRule::SocketRoutingRule(LocalEndpointRulePtr local_rule, RemoteEndpointRulePtr remote_rule, string route_description /* = "" */)
    {
        local_endpoint_rule = local_rule;
        remote_endpoint_rule = remote_rule;
        description = route_description;
    }

    SocketRoutingRule::~SocketRoutingRule()
    {
    }

    void SocketRoutingRule::Load(const ConfigProperties& cfg, const EndpointRuleFactory& factory)
    {
        const ConfigProperties& local_cfg = cfg.get_child("local");
        LocalEndpointRulePtr local_rule = factory.LoadLocal(local_cfg);

        const ConfigProperties& remote_cfg = cfg.get_child("remote");
        RemoteEndpointRulePtr remote_rule = factory.LoadRemote(remote_cfg);

        local_endpoint_rule = local_rule;
        remote_endpoint_rule = remote_rule;
    }

    ConfigProperties SocketRoutingRule::Save()
    {
        ConfigProperties cfg = RoutingRule::Save();

        cfg.add_child("local", local_endpoint_rule->Save());
        cfg.add_child("remote", remote_endpoint_rule->Save());
        return cfg;
    }

    AcceptorPtr SocketRoutingRule::CreateAcceptor(const Acceptor::Handler& handler)
    {
        return local_endpoint_rule->CreateAcceptor(handler);
    }

    SessionPtr SocketRoutingRule::CreateSession(const EndpointPtr& endpoint)
    {
        return make_shared<SocketSession>(endpoint, shared_from_this());
    }

    ConnectorPtr SocketRoutingRule::CreateConnector(const Connector::Handler& handler)
    {
        return remote_endpoint_rule->CreateConnector(handler);
    }
}