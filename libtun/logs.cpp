#include "stdafx.h"
#include "logs.h"

#include <log4cplus/configurator.h>
#include <log4cplus/hierarchy.h>
#include <log4cplus/consoleappender.h>
#include <log4cplus/fileappender.h>
#include <log4cplus/win32debugappender.h>

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

        void AddDebugAppender(Logger& logger)
        {
            log4cplus::SharedAppenderPtr appender(new log4cplus::Win32DebugAppender());
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

        static bool _logging_initialized;

        static void InitLogging()
        {
            if (!_logging_initialized)
            {
                _logging_initialized = true;
                log4cplus::initialize();

                log4cplus::SharedAppenderPtr appender(new log4cplus::Win32DebugAppender());
                for (Logger& logger : log4cplus::getDefaultHierarchy().getCurrentLoggers())
                {
                    logger.addAppender(appender);
                }
            }
        }

        void EnableLogging()
        {
            InitLogging();
            Logger::getDefaultHierarchy().enableAll();
        }
    }
}