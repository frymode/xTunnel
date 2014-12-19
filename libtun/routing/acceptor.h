#pragma once

#include "endpoint.h"

namespace xTunnel
{
    class Acceptor : public noncopyable
    {
    public:
        typedef AsyncResult<EndpointPtr> AcceptResult;
        typedef function<void(const AcceptResult& res)> Handler;

        virtual ~Acceptor() = 0;
        virtual void Start(const Handler& handler);

    protected:
        virtual void BeginAccept() = 0;
        void OnAccept(const AcceptResult& res);

    private:
        Mutex _mutex;
        Handler _handler;
    };

    typedef shared_ptr<Acceptor> AcceptorPtr;
}