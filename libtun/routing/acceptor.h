#pragma once

#include "endpoint.h"

namespace xTunnel
{
    class Acceptor : public noncopyable
    {
    public:
        typedef AsyncResult<EndpointPtr> AcceptResult;
        typedef function<void(const AcceptResult& res)> Handler;

        Acceptor(const Handler& handler);
        virtual ~Acceptor() = 0;

    protected:
        void OnAccept(const AcceptResult& res);

    private:
        Mutex _mutex;
        Handler _handler;
    };

    typedef shared_ptr<Acceptor> AcceptorPtr;
}