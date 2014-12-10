#include "stdafx.h"
#include "routing_rule.h"

namespace xTunnel
{
    RoutingRule::RoutingRule()
    {
        initially_started = false;
        idle_timeout_in_sec = 0;
    }

    RoutingRule::~RoutingRule()
    {
    }

    void RoutingRule::Load(const ConfigProperties& cfg, const EndpointRuleFactory& factory)
    {
        initially_started = cfg.get<bool>("initially_started", false);
        idle_timeout_in_sec = cfg.get<int>("idle_timeout_in_sec", 0);
        description = cfg.get<string>("description", "");
    }

    ConfigProperties RoutingRule::Save()
    {
        ConfigProperties cfg;
        cfg.add<bool>("initially_started", initially_started);
        cfg.add<int>("idle_timeout_in_sec", idle_timeout_in_sec);
        cfg.add<string>("description", description);

        return cfg;
    }
}