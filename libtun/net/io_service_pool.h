#pragma once

namespace xTunnel
{
    class io_service_pool : noncopyable
    {
    public:
        static io_service_pool& default();
        static io_service& get_io_service();

        explicit io_service_pool(size_t pool_size);

        void Run();
        void Stop();

        io_service_ptr& GetService();

    private:
        typedef shared_ptr<io_service::work> work_ptr;

        vector<io_service_ptr> io_services_;
        vector<work_ptr> work_;
        atomic<size_t> next_io_service_;
    };
}