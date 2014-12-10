#include "stdafx.h"
#include "endpoint_rule.h"

namespace xTunnel
{
    EndpointRule::~EndpointRule()
    {
    }

	string EndpointRule::description() const
	{
		ConfigProperties cfg = Save();
		
		string buf;
		for (auto i = cfg.begin(); i != cfg.end(); ++i)
		{
			if (!buf.empty())
			{
				buf.append(", ");
			}
			buf.append(i->first);
			buf.append(": ");
			buf.append(i->second.data());
		}

		return buf;
	}

    ConfigProperties EndpointRule::Save() const
    {
        ConfigProperties cfg;
        cfg.add("type", name());
        
        return cfg;
    }
}