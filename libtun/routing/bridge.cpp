#include "stdafx.h"
#include "bridge.h"

namespace xTunnel
{
    Bridge::Bridge(const EndpointPtr& downstream, const EndpointPtr& upstream)
        : _downstream(downstream),
          _upstream(upstream)
    {
        _downstream->BeginReceive([this](const Endpoint::ReceiveResult& res)
        {
            const DataBuffer& buf = res.data();
            OnDataReceived(*_downstream, buf.data, buf.size);
        });
        _upstream->BeginReceive([this](const Endpoint::ReceiveResult& res)
        {
            const DataBuffer& buf = res.data();
            OnDataReceived(*_upstream, buf.data, buf.size);
        });
    }

    Bridge::~Bridge()
    {
    }

    double Bridge::transfer_speed() const
    {
        _speedometer.SetValue(_downstream->total_sent() + _upstream->total_sent());
        return _speedometer.speed();
    }

    void Bridge::OnDataReceived(Endpoint& endpoint, const char* data, int size)
    {
        Opposite(&endpoint)->Send(data, size);
    }
}