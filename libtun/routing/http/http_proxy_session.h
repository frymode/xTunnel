#pragma once

#include "routing/session.h"
#include "routing/endpoint.h"

namespace xTunnel
{
    class HttpProxySession : public Session
    {
    public:
        HttpProxySession(const EndpointPtr& local_endpoint);
        virtual ~HttpProxySession();

        virtual double transfer_speed() const override { return 0; }

    private:
        EndpointPtr local_endpoint_;
    };
}