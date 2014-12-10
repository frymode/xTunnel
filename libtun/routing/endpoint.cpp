#include "stdafx.h"
#include "endpoint.h"

namespace xTunnel
{
	Endpoint::Endpoint(const EndpointRulePtr& rule, const EndpointState& state /* = kClosed */)
        : _rule(rule),
          _state(state)
    {
    }

    Endpoint::~Endpoint()
    {
    }

    void Endpoint::Close()
    {
        SetState(kClosed);
    }

    void Endpoint::SetState(const EndpointState& state)
    {
        if (_state != state)
        {
            _state = state;
        }
    }
}