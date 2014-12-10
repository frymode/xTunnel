#pragma once

#include "routing/rules/routing_rule.h"

namespace xTunnel
{
    class SocketRoutingRule : public RoutingRule
    {
    public:
        SocketRoutingRule();
        SocketRoutingRule(LocalEndpointRulePtr local_rule, RemoteEndpointRulePtr remote_rule, string route_description = "");
        virtual ~SocketRoutingRule();

        virtual void Load(const ConfigProperties& cfg, const EndpointRuleFactory& factory) override;
        virtual ConfigProperties Save() override;

        virtual AcceptorPtr CreateAcceptor(const Acceptor::Handler& handler) override;
        virtual SessionPtr CreateSession(const EndpointPtr& endpoint) override;
        virtual ConnectorPtr CreateConnector(const Connector::Handler& handler);

        LocalEndpointRulePtr local_endpoint_rule;
        RemoteEndpointRulePtr remote_endpoint_rule;

        shared_ptr<SocketRoutingRule> shared_from_this()
        {
            return static_pointer_cast<SocketRoutingRule>(RoutingRule::shared_from_this());
        }
    };

    typedef shared_ptr<SocketRoutingRule> SocketRoutingRulePtr;
}