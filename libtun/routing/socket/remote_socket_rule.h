#pragma once

#include "../rules/remote_endpoint_rule.h"

namespace xTunnel
{
    class RemoteSocketRule : public RemoteEndpointRule
    {
    public:
        virtual string name() const { return "socket"; }

        RemoteSocketRule();
        virtual ~RemoteSocketRule();

        virtual void Load(const ConfigProperties& cfg) override;
        virtual ConfigProperties Save() const override;

        virtual ConnectorPtr CreateConnector(const Connector::Handler& handler) override;

        string host;
        int port;
    };

    typedef shared_ptr<RemoteSocketRule> RemoteSocketRulePtr;
}