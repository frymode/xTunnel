#include "stdafx.h"
#include "http_proxy_rule.h"
#include "http_proxy_session.h"

namespace xTunnel
{
    HttpProxyRule::HttpProxyRule(const LocalEndpointRulePtr& local_rule)
    {
        local_endpoint_rule = local_rule;
    }

    HttpProxyRule::~HttpProxyRule()
    {
    }

    AcceptorPtr HttpProxyRule::CreateAcceptor(const Acceptor::Handler& handler)
    {
        return local_endpoint_rule->CreateAcceptor(handler);
    }

    SessionPtr HttpProxyRule::CreateSession(const EndpointPtr& endpoint)
    {
        return make_shared<HttpProxySession>(endpoint);
    }
}