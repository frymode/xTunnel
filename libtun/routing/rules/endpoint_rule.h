#pragma once

namespace xTunnel
{
    class EndpointRule : public enable_shared_from_this<EndpointRule>
    {
    public:
        virtual ~EndpointRule() = 0;
        
        virtual string name() const = 0;
		virtual string description() const;

        virtual void Load(const ConfigProperties& cfg) = 0;
        virtual ConfigProperties Save() const;
    };

    typedef shared_ptr<EndpointRule> EndpointRulePtr;
}