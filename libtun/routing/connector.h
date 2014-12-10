#pragma once

#include "endpoint.h"

namespace xTunnel
{
    class Connector
    {
    public:
        typedef AsyncResult<EndpointPtr> ConnectResult;
        typedef function<void(const ConnectResult& res)> Handler;

        Connector(const Handler& handler);
        virtual ~Connector() = 0;

    protected:
        void OnConnect(const ConnectResult& res);
    
    private:
        Mutex _mutex;
        Handler _handler;
    };

    typedef shared_ptr<Connector> ConnectorPtr;
}