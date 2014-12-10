#include "stdafx.h"
#include "acceptor.h"

namespace xTunnel
{
    Acceptor::Acceptor(const Handler& handler)
        : _handler(handler)
    {
    }

    Acceptor::~Acceptor()
    {
        UniqueLock lock(_mutex);
        _handler = Handler();
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