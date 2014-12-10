#include "stdafx.h"
#include "endpoint_rule_factory.h"

namespace xTunnel
{
    LocalEndpointRulePtr EndpointRuleFactory::LoadLocal(const ConfigProperties& cfg) const
    {
        return local_rules_registry_.Load(cfg);
    }
    
    RemoteEndpointRulePtr EndpointRuleFactory::LoadRemote(const ConfigProperties& cfg) const
    {
        return remote_rules_registry_.Load(cfg);
    }
}