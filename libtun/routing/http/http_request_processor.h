#pragma once

#include "routing/endpoint.h"

namespace xTunnel
{
    class HttpRequestProcessor
    {
    public:
        virtual ~HttpRequestProcessor();

        void OnDataReceived(Endpoint& endpoint, const char* data, int size);
    private:
        string http_method;
        string http_url;
    };
}