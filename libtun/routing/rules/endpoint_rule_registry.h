#pragma once

#include "local_endpoint_rule.h"
#include "remote_endpoint_rule.h"
#include "factory.h"

namespace xTunnel
{
    template <typename TRule>
    class EndpointRuleRegistry
    {
    public:
        typedef Factory<TRule> RuleFactory;
        typedef shared_ptr<RuleFactory> RuleFactoryPtr;

        template <typename TEndpointRule>
        void Register()
        {
            TEndpointRule rule;
            string rule_name = rule.name();

            RuleFactoryPtr factory = RuleFactory::Subclass<TEndpointRule>();
            rules_[rule_name] = factory;
        }

        shared_ptr<TRule> Load(const ConfigProperties& cfg) const
        {
            string rule_name = cfg.get("type", "");
            auto i = rules_.find(rule_name);
            if (i == rules_.end())
            {
                return nullptr;
            }

            RuleFactoryPtr factory = i->second;
            shared_ptr<TRule> rule = factory->Create();
            rule->Load(cfg);
            return rule;
        }
    private:
        EndpointRulePtr LoadEndpointRule(const ConfigProperties& cfg);
        map<string, RuleFactoryPtr> rules_;
    };

    typedef EndpointRuleRegistry<LocalEndpointRule> LocalEndpointRuleRegistry;
    typedef EndpointRuleRegistry<RemoteEndpointRule> RemoteEndpointRuleRegistry;
}