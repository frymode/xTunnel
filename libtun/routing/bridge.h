#pragma once

#include "endpoint.h"
#include "speedometer.h"

namespace xTunnel
{
    class Bridge
    {
    public:
        Bridge(const EndpointPtr& downstream, const EndpointPtr& upstream);
        virtual ~Bridge();

        double transfer_speed() const;

    protected:
        void OnDataReceived(Endpoint& endpoint, const char* data, int size);

        inline Endpoint* Opposite(Endpoint* endpoint)
        {
            if (endpoint == _upstream.get())
            {
                return _downstream.get();
            }
            else
            {
                return _upstream.get();
            }
        }

    private:
        EndpointPtr _downstream;
        EndpointPtr _upstream;
        mutable Speedometer _speedometer;
    };

    typedef shared_ptr<Bridge> BridgePtr;
}