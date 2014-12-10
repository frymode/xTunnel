#pragma once

#include <boost/thread.hpp>
#include <mutex>
#include <memory>

namespace xTunnel
{
    typedef boost::thread Thread;
    typedef std::shared_ptr<Thread> ThreadPtr;

    using boost::thread_specific_ptr;

    typedef std::mutex Mutex; // non recursive
    typedef std::unique_lock<Mutex> UniqueLock;
}