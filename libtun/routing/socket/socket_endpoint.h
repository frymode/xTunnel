#pragma once

#include "routing/endpoint.h"

#include "net/socket.h"
#include "net/buffer_policy.h"

namespace xTunnel
{
    class SocketEndpoint : public Endpoint
    {
    public:
        SocketEndpoint(const EndpointRulePtr& rule, const SocketPtr& socket);
        virtual ~SocketEndpoint();

        virtual void BeginReceive(const ReceiveHandler& handler) override;
        virtual void Send(const char* buf, int size) override;
        virtual void Close() override;

    protected:
        void BeginReceive();
        void HandleReceive(const ErrorCode& error, const size_t& bytes_received);
        void HandleSend(const ErrorCode& error, const size_t& bytes_sent);
        bool SendQueue();

    private:
        ReceiveHandler _handler;
        ErrorCode error_;
        atomic<bool> _sending;
        SocketPtr _socket;
        DataBuffer buf_;
        BufferPolicy buf_policy_;
        DataBuffer _out_buf;
        DataBuffer _out_queue;
    };
}