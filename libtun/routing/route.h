#pragma once

#include "rules/routing_rule.h"
#include "session.h"

namespace xTunnel
{
    class Route
    {
    public:
        Route(const RoutingRulePtr& rule);

        void Activate();
        void Deactivate();
        bool isActive() const;

        const RoutingRulePtr& rule() const { return _rule; }
        double transfer_speed() const;

    private:
        void HandleAccept(const Acceptor::AcceptResult& res);

        const RoutingRulePtr _rule;
        AcceptorPtr _acceptor;

        mutable Mutex _mutex;
        unordered_set<SessionPtr> _sessions;
    };
}