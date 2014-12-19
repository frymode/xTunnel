#pragma once

#include <WinSDKVer.h>

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0502   // Windows XP
#endif

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
#include <winsock2.h>
#include <windows.h>

#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <string.h>
#include <process.h>

#include <string>
#include <vector>
#include <memory>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <iostream>
#include <sstream>
#include <functional>
#include <iterator>
#include <algorithm>

#include <boost/noncopyable.hpp>
#include <boost/format.hpp>
#include <boost/scoped_array.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/asio.hpp>

namespace xTunnel
{
    using namespace std;
    using namespace std::placeholders;

    using boost::noncopyable;
    using boost::format;
    using boost::str;
    using boost::scoped_array;

    using boost::starts_with;

    namespace io
    {
        using namespace boost::io;
    }

    using boost::asio::io_service;
    typedef shared_ptr<boost::asio::io_service> io_service_ptr;

    using boost::asio::ip::tcp;
}

#include "exception.h"
#include "logs.h"
#include "threading.h"
#include "timer.h"
#include "strutil.h"