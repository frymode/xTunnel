#pragma once

#include "local_socket_rule.h"
#include "net/socket.h"
#include "routing/acceptor.h"

namespace xTunnel
{
    class SocketAcceptor : public Acceptor, public enable_shared_from_this<SocketAcceptor>
    {
    public:
        SocketAcceptor(const LocalSocketRulePtr& rule);
        virtual ~SocketAcceptor();

        const LocalSocketRule& rule() const { return *_rule; }

    private:
        virtual void BeginAccept() override;
        void EndAccept(const SocketPtr& socket, const ErrorCode& error);
        static void HandleAccept(weak_ptr<SocketAcceptor> self, SocketPtr socket, const ErrorCode& error);

        LocalSocketRulePtr _rule;
        tcp::acceptor _impl;
    };
}