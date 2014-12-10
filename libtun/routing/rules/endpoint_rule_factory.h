#pragma once

#include "endpoint_rule_registry.h"

namespace xTunnel
{
    class EndpointRuleFactory
    {
    public:
        template <typename TLocalRule, typename TRemoteRule>
        void Register()
        {
            RegisterLocal<TLocalRule>();
            RegisterRemote<TRemoteRule>();
        }
        
        template <typename TLocalRule>
        void RegisterLocal() { local_rules_registry_.Register<TLocalRule>(); }

        template <typename TRemoteRule>
        void RegisterRemote() { remote_rules_registry_.Register<TRemoteRule>(); }

        LocalEndpointRulePtr LoadLocal(const ConfigProperties& cfg) const;
        RemoteEndpointRulePtr LoadRemote(const ConfigProperties& cfg) const;

    private:
        LocalEndpointRuleRegistry local_rules_registry_;
        RemoteEndpointRuleRegistry remote_rules_registry_;
    };
}