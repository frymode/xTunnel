#pragma once

namespace xTunnel
{
    class Session
    {
    public:
        virtual ~Session() = 0;
        virtual double transfer_speed() const = 0;
    };

    typedef shared_ptr<Session> SessionPtr;
}