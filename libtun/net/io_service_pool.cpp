#include "stdafx.h"
#include "io_service_pool.h"

namespace xTunnel
{
    static Mutex default_pool_mutex_;
    static unique_ptr<io_service_pool> default_io_pool_;

    io_service_pool& io_service_pool::default()
    {
        if (!default_io_pool_)
        {
            UniqueLock lock(default_pool_mutex_);
            if (!default_io_pool_)
            {
                int pool_size = max(Thread::hardware_concurrency(), 1);
                default_io_pool_ = make_unique<io_service_pool>(pool_size);
            }
        }
        return *default_io_pool_;
    }

    io_service& io_service_pool::get_io_service()
    {
        return *default().GetService();
    }

    io_service_pool::io_service_pool(size_t pool_size)
        : next_io_service_(0)
    {
        if (pool_size <= 0)
        {
			THROW_ARGUMENT_ERROR("pool_size", "must be greater than zero");
        }

        for (size_t i = 0; i < pool_size; ++i)
        {
            auto service = make_shared<io_service>();
            auto work = make_shared<io_service::work>(*service);
            io_services_.push_back(service);
            work_.push_back(work);
        }
    }

    void io_service_pool::Run()
    {
        vector<ThreadPtr> threads;
        for (size_t i = 0; i < io_services_.size(); ++i)
        {
            auto thread = make_shared<Thread>(boost::bind(&io_service::run, io_services_[i]));
            threads.push_back(thread);
        }

        for (size_t i = 0; i < threads.size(); ++i)
        {
            threads[i]->join();
        }
    }

    void io_service_pool::Stop()
    {
        for (size_t i = 0; i < io_services_.size(); ++i)
        {
            io_services_[i]->stop();
        }
    }

    io_service_ptr& io_service_pool::GetService()
    {
        auto& service = io_services_[next_io_service_];
        ++next_io_service_;
        if (next_io_service_ == io_services_.size())
            next_io_service_ = 0;
        return service;
    }
}