#pragma once

#include <chrono>

namespace xTunnel
{
    class Timer
    {
    public:
        typedef std::chrono::high_resolution_clock Clock;

        Timer()
        {
            _start_time = Clock::now();
        }

        double ElapsedSeconds() const
        {
            return ElapsedMilliseconds() / 1000.0;
        }

        uint64_t ElapsedMilliseconds() const
        {
            Clock::time_point now = Clock::now();
            return std::chrono::duration_cast<std::chrono::milliseconds>(now - _start_time).count();
        }

        void Reset()
        {
            _start_time = Clock::now();
        }

        double ResetSeconds()
        {
            return ResetMilliseconds() / 1000.0;
        }

        uint64_t ResetMilliseconds()
        {
            Clock::time_point now = Clock::now();
            uint64_t res = std::chrono::duration_cast<std::chrono::milliseconds>(now - _start_time).count();
            _start_time = now;
            return res;
        }

    private:
        Clock::time_point _start_time;
    };
}