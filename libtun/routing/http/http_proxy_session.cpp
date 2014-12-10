#include "stdafx.h"
#include "http_proxy_session.h"

namespace xTunnel
{
    HttpProxySession::HttpProxySession(const EndpointPtr& local_endpoint)
        : local_endpoint_(local_endpoint)
    {
        //local_endpoint_->BeginReceive(this);
    }

    HttpProxySession::~HttpProxySession()
    {
    }
}