#pragma once

#include "endpoint_rule.h"
#include "routing/acceptor.h"

namespace xTunnel
{
    class LocalEndpointRule : public EndpointRule
    {
    public:
        virtual ~LocalEndpointRule() = 0;
        virtual AcceptorPtr CreateAcceptor(const Acceptor::Handler& handler) = 0;
    };

    typedef shared_ptr<LocalEndpointRule> LocalEndpointRulePtr;
}