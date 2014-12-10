#include "stdafx.h"
#include "buffer_policy.h"

namespace xTunnel
{
    static int CalcSize(int old, int size)
    {
        if (size >= old)
        {
            if (size < 512)
            {
                return size * 4;
            }
            else if (size < 16536)
            {
                return size * 2;
            }
            else 
            {
                return size / 2 * 3;
            }
        }
        else if (size > 512 && size < old / 4)
        {
            return old / 2;
        }
        else
        {
            return old;
        }
    }

    BufferPolicy::BufferPolicy(int initial_size /* = 4096 */)
    {
        size_ = initial_size;
    }

    int BufferPolicy::GetSize() const
    {
        return size_;
    }

    void BufferPolicy::SetUsedSize(int size)
    {
        size_ = CalcSize(size_, size);
    }
}