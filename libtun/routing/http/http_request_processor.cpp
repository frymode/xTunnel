#include "stdafx.h"
#include "http_request_processor.h"

namespace xTunnel
{
    HttpRequestProcessor::~HttpRequestProcessor()
    {
    }

    void HttpRequestProcessor::OnDataReceived(Endpoint& endpoint, const char* data, int size)
    {
    }
}