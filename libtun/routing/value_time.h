#pragma once

namespace xTunnel
{
    template<typename T>
    struct ValueTime
    {
        typedef T ValueType;
        typedef unsigned __int64 TimeType;

        ValueTime() 
            : value(0), time(0) 
        { 
        }
        
        ValueTime(const ValueType& val, TimeType val_time) 
            : value(val), time(val_time) 
        {
        }

        ValueType value;
        TimeType time;
    };
}