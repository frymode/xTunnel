#include "stdafx.h"
#include "route.h"
#include "socket/socket_endpoint.h"

namespace xTunnel
{
    Route::Route(const RoutingRulePtr& rule)
        : _rule(rule)
    {
    }

    double Route::transfer_speed() const
    {
        UniqueLock lock(_mutex);
        
        double speed = 0;
        for (auto& session: _sessions)
        {
            speed += session->transfer_speed();
        }

        return speed;
    }

    void Route::Activate()
    {
        LOG_INFO(logs::app, "Activating route " << _rule->description);
        UniqueLock lock(_mutex);
        if (!_acceptor)
        {
            _acceptor = _rule->CreateAcceptor([this](const Acceptor::AcceptResult& res)
            {
                HandleAccept(res);
            });
            LOG_DEBUG(logs::app, "Route activated");
        }
        else
        {
            LOG_DEBUG(logs::app, "Route already active");
        }
    }

    void Route::Deactivate()
    {
        LOG_INFO(logs::app, "Deactivating route " << _rule->description);
        UniqueLock lock(_mutex);
        if (!_acceptor)
        {
            LOG_DEBUG(logs::app, "Route already deactivated");
        }

        _acceptor.reset();
        _sessions.clear();
        LOG_DEBUG(logs::app, "Route deactivated");
    }

    bool Route::isActive() const
    {
        UniqueLock lock(_mutex);
        return _acceptor != nullptr;
    }

    void Route::HandleAccept(const Acceptor::AcceptResult& res)
	{
        UniqueLock lock(_mutex);
        if (_acceptor)
        {
            if (!res.succeeded())
            {
                _acceptor.reset();
                return;
            }

            const EndpointPtr& endpoint = res.data();

            LOG_INFO(logs::app, "Accepted connection at " << endpoint->rule()->description());
            SessionPtr session = _rule->CreateSession(endpoint);
            _sessions.insert(move(session));
        }
	}
}