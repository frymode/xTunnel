#pragma once

#include "routing/rules/routing_rule.h"

namespace xTunnel
{
    class HttpProxyRule : public RoutingRule
    {
    public:
        HttpProxyRule(const LocalEndpointRulePtr& local_rule);
        virtual ~HttpProxyRule();

        virtual void Load(const ConfigProperties& cfg, const EndpointRuleFactory& factory);
        virtual ConfigProperties Save();

        virtual AcceptorPtr CreateAcceptor(const Acceptor::Handler& handler) override;
        virtual SessionPtr CreateSession(const EndpointPtr& endpoint) override;

        LocalEndpointRulePtr local_endpoint_rule;
    };
}