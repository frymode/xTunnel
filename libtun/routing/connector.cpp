#include "stdafx.h"
#include "connector.h"

namespace xTunnel
{
    Connector::~Connector()
    {
        UniqueLock lock(_mutex);
        _handler = Handler();
    }

    void Connector::Start(const Handler& handler)
    {
        UniqueLock lock(_mutex);
        _handler = handler;
        lock.unlock();

        BeginConnect();
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