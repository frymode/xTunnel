#include "stdafx.h"
#include "socket_session.h"

namespace xTunnel
{
    SocketSession::SocketSession(const EndpointPtr& downstream, const SocketRoutingRulePtr& rule)
        : _downstream(downstream),
          _rule(rule)
    {
        _connector = _rule->CreateConnector([this](const Connector::ConnectResult& res)
        {
            HandleConnect(res);
        });
    }

    SocketSession::~SocketSession()
    {
        UniqueLock lock(_mutex);
        _connector.reset();
    }

    double SocketSession::transfer_speed() const
    {
        UniqueLock lock(_mutex);
        if (_bridge)
        {
            return _bridge->transfer_speed();
        }
        return 0;
    }

    void SocketSession::HandleConnect(const Connector::ConnectResult& res)
    {
        UniqueLock lock(_mutex);
        _connector.reset();
        if (res.succeeded())
        {
            _bridge = make_shared<Bridge>(_downstream, res.data());
        }
    }
}