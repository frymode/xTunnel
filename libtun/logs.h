#pragma once

#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>
#include "config.h"

#define LOG_MSG(logger, level, message)  LOG4CPLUS_MACRO_BODY(logger, message, level)

#define LOG_TRACE   LOG4CPLUS_TRACE
#define LOG_DEBUG   LOG4CPLUS_DEBUG
#define LOG_INFO    LOG4CPLUS_INFO
#define LOG_WARN    LOG4CPLUS_WARN
#define LOG_ERROR   LOG4CPLUS_ERROR
#define LOG_FATAL   LOG4CPLUS_FATAL

namespace xTunnel
{
    typedef log4cplus::Logger Logger;

    namespace logs
    {
        enum Level
        {
            kTrace   = log4cplus::TRACE_LOG_LEVEL,
            kDebug   = log4cplus::DEBUG_LOG_LEVEL,
            kInfo    = log4cplus::INFO_LOG_LEVEL,
            kWarning = log4cplus::WARN_LOG_LEVEL,
            kError   = log4cplus::ERROR_LOG_LEVEL,
            kFatal   = log4cplus::FATAL_LOG_LEVEL,
        };

        extern Logger net;
        extern Logger db;
        extern Logger data;
        extern Logger app;
        extern Logger test;

        void ConfigureLoggers(const string& config_path = "logs.cfg");
        void ConfigureLoggers(const Config& config);

        void AddConsoleAppender(Logger& logger);
        void AddFileAppender(Logger& logger, const string& path);

        void DisableLogging();
        void EnableLogging();
    }
}
