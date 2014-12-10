#pragma once

#include "../rules/local_endpoint_rule.h"

namespace xTunnel
{
    class LocalSocketRule : public LocalEndpointRule
    {
    public:
        virtual string name() const override { return "socket"; }
        virtual ~LocalSocketRule();

        virtual void Load(const ConfigProperties& cfg) override;
        virtual ConfigProperties Save() const override;

        virtual AcceptorPtr CreateAcceptor(const Acceptor::Handler& handler) override;

        int port;
    };

    typedef shared_ptr<LocalSocketRule> LocalSocketRulePtr;
}