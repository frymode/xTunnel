#include "stdafx.h"
#include "connector.h"

namespace xTunnel
{
    Connector::Connector(const Handler& handler)
        : _handler(handler)
    {
    }

    Connector::~Connector()
    {
        UniqueLock lock(_mutex);
        _handler = Handler();
    }

    void Connector::OnConnect(const ConnectResult& res)
    {
        UniqueLock lock(_mutex);
        if (_handler)
        {
            _handler(res);
        }
    }
}