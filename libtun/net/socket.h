#pragma once

namespace xTunnel
{
    typedef tcp::socket Socket;
	typedef shared_ptr<Socket> SocketPtr;
	typedef boost::system::error_code ErrorCode;
}