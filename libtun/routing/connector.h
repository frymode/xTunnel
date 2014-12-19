#pragma once

#include "endpoint.h"

namespace xTunnel
{
    class Connector
    {
    public:
        typedef AsyncResult<EndpointPtr> ConnectResult;
        typedef function<void(const ConnectResult& res)> Handler;

        virtual ~Connector() = 0;
        virtual void Start(const Handler& handler);

    protected:
        virtual void BeginConnect() = 0;
        void OnConnect(const ConnectResult& res);

    private:
        Mutex _mutex;
        Handler _handler;
    };

    typedef shared_ptr<Connector> ConnectorPtr;
}