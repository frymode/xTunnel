#include "stdafx.h"
#include "acceptor.h"

namespace xTunnel
{
    Acceptor::~Acceptor()
    {
        UniqueLock lock(_mutex);
        _handler = Handler();
    }

    void Acceptor::Start(const Handler& handler)
    {
        UniqueLock lock(_mutex);
        _handler = handler;
        lock.unlock();

        BeginAccept();
    }

    void Acceptor::OnAccept(const AcceptResult& res)
    {
        UniqueLock lock(_mutex);
        if (_handler)
        {
            _handler(res);
        }
    }
}