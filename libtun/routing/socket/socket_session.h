#pragma once

#include "routing/session.h"
#include "routing/bridge.h"
#include "socket_routing_rule.h"

namespace xTunnel
{
    class SocketSession : public Session, public enable_shared_from_this<SocketSession>
    {
    public:
        SocketSession(const EndpointPtr& downstream, const SocketRoutingRulePtr& rule);
        virtual ~SocketSession();

        virtual double transfer_speed() const override;

        const Bridge* bridge() const { return _bridge.get(); }

    private:
        void HandleConnect(const Connector::ConnectResult& res);

        EndpointPtr _downstream;
        SocketRoutingRulePtr _rule;

        mutable Mutex _mutex;
        ConnectorPtr _connector;
        BridgePtr _bridge;
    };
}