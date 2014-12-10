#pragma once

#include <boost/property_tree/ptree.hpp>

namespace xTunnel
{
    typedef boost::property_tree::ptree ConfigProperties;

    enum ConfigFileFormat
    {
        CONFIG_FORMAT_UNDEFINED = 0,
        CONFIG_FORMAT_INI       = 1,
        CONFIG_FORMAT_XML       = 2,
        CONFIG_FORMAT_JSON      = 3,
        CONFIG_FORMAT_INFO      = 4,
    };

    class Config : noncopyable
    {
    public:
        virtual bool Load(const string& path, ConfigFileFormat format = CONFIG_FORMAT_UNDEFINED);
        virtual bool Save(const string& path, ConfigFileFormat format = CONFIG_FORMAT_UNDEFINED) const;

        ConfigProperties& properties() { return _properties; }
        const ConfigProperties& properties() const { return _properties; }
        void SetProperties(const ConfigProperties& props);

        const ConfigProperties* get_child(const string& key) const;

        template <typename T>
        T get(const string& key) const
        {
            return _properties.get<T>(key);
        }

        template <typename T>
        T get(const string& key, const T& default_value) const
        {
            return _properties.get<T>(key, default_value);
        }

        string get(const string& key) const
        {
            return _properties.get<string>(key);
        }

        string get(const string& key, const string& default_value) const
        {
            return _properties.get<string>(key, default_value);
        }

    private:
        ConfigProperties _properties;
    };
}