#pragma once

#include "endpoint_rule.h"
#include "routing/connector.h"

namespace xTunnel
{
    class RemoteEndpointRule : public EndpointRule
    {
    public:
        virtual ~RemoteEndpointRule() = 0;
        virtual ConnectorPtr CreateConnector(const Connector::Handler& handler) = 0;
    };

    typedef shared_ptr<RemoteEndpointRule> RemoteEndpointRulePtr;
}