#include "stdafx.h"
#include "logs.h"

#include <log4cplus/configurator.h>
#include <log4cplus/hierarchy.h>
#include <log4cplus/consoleappender.h>
#include <log4cplus/fileappender.h>

namespace xTunnel
{
    namespace logs
    {
        Logger net  = Logger::getInstance("net");
        Logger db   = Logger::getInstance("db");
        Logger data = Logger::getInstance("data");
        Logger app  = Logger::getInstance("app");
        Logger test = Logger::getInstance("test");

        void ConfigureLoggers(const string& config_path /* = "logs.cfg" */)
        {
            log4cplus::PropertyConfigurator::doConfigure(config_path);
        }

        void ConfigureLoggers(const Config& config)
        {
            const ConfigProperties* props = config.get_child("logs");
            if (!props)
            {
                THROW_EXCEPTION("Cannot find logs config section");
            }

            stringstream stream;
            for (auto i = props->begin(); i != props->end(); ++i)
            {
                string key = i->first;
                string value = i->second.get_value<string>();

                if (!starts_with(key, "log4cplus."))
                {
                    key = "log4cplus." + key;
                }
                stream << key << "=" << value << endl;
            }

            log4cplus::PropertyConfigurator configurator(stream);
            configurator.configure();
        }

        void AddConsoleAppender(Logger& logger)
        {
            log4cplus::SharedAppenderPtr appender(new log4cplus::ConsoleAppender());
            logger.addAppender(appender);
        }

        void AddFileAppender(Logger& logger, const string& path)
        {
            log4cplus::SharedAppenderPtr appender(new log4cplus::FileAppender(path));
            logger.addAppender(appender);
        }

        void DisableLogging()
        {
            Logger::getDefaultHierarchy().disableAll();
        }

        void EnableLogging()
        {
            Logger::getDefaultHierarchy().enableAll();
        }
    }
}