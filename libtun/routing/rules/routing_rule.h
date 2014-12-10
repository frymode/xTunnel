#pragma once

#include "local_endpoint_rule.h"
#include "remote_endpoint_rule.h"
#include "endpoint_rule_factory.h"
#include "routing/session.h"

namespace xTunnel
{
    class RoutingRule : public enable_shared_from_this<RoutingRule>
    {
    public:
        RoutingRule();
        virtual ~RoutingRule();

        virtual void Load(const ConfigProperties& cfg, const EndpointRuleFactory& factory);
        virtual ConfigProperties Save();

        virtual AcceptorPtr CreateAcceptor(const Acceptor::Handler& handler) = 0;
        virtual SessionPtr CreateSession(const EndpointPtr& endpoint) = 0;

        string description;
        bool initially_started;
        int idle_timeout_in_sec;
    };

    typedef shared_ptr<RoutingRule> RoutingRulePtr;
}
