#pragma once

#include "routing/connector.h"
#include "remote_socket_rule.h"
#include "net/socket.h"

namespace xTunnel
{
    class SocketConnector : public Connector, public enable_shared_from_this<SocketConnector>
    {
    public:
        SocketConnector(const RemoteSocketRulePtr& rule);
        virtual ~SocketConnector();

    private:
        virtual void BeginConnect() override;
        void EndConnect(const ErrorCode& error);
        static void HandleConnect(weak_ptr<SocketConnector> self, const ErrorCode& error);

    private:
        RemoteSocketRulePtr _rule;
        Mutex _mutex;
        SocketPtr _socket;
    };
}