#pragma once

namespace xTunnel
{
    struct DataBuffer
    {
        DataBuffer()
            : data(nullptr), size(0), buf_size(0)
        {
        }

        DataBuffer(size_t initial_size)
            : size(initial_size),
              buf_size(initial_size)
        {
            data = (char*)malloc(initial_size);
        }

        DataBuffer(const char* src, size_t src_size)
            : size(src_size), 
              buf_size(src_size)
        {
            data = (char*)malloc(src_size);
            memcpy(data, src, src_size);
        }

        DataBuffer(const DataBuffer& other)
        {
            if (other.size > 0)
            {
                buf_size = size = other.size;
                data = (char*)malloc(size);
                memcpy(data, other.data, size);
            }
            else
            {
                data = nullptr;
                buf_size = size = 0;
            }
        }

        DataBuffer(DataBuffer&& other)
        {
            data = other.data;
            size = other.size;
            buf_size = other.buf_size;

            other.data = nullptr;
            other.size = 0;
            other.buf_size = 0;
        }

        ~DataBuffer()
        {
            free(data);
        }

        DataBuffer& operator = (const DataBuffer& other)
        {
            if (&other != this)
            {
                Reset(other.data, other.size);
            }
            return *this;
        }

        void Swap(DataBuffer& other)
        {
            swap(*this, other);
        }

        void Reset()
        {
            size = 0;
        }

        void Reset(size_t new_size)
        {
            buf_size = size = new_size;
            data = (char*)realloc(data, new_size);
        }

        void Reset(const char* src, size_t src_size)
        {
            if (src_size > buf_size || src_size < buf_size / 4)
            {
                buf_size = size = src_size;
                data = (char*)realloc(data, src_size);
            }
            else
            {
                size = src_size;
            }
            memcpy(data, src, src_size);
        }

        void Append(const char* src, size_t src_size)
        {
            if (size + src_size > buf_size)
            {
                buf_size = size + src_size;
                data = (char*)realloc(data, buf_size);
            }
            memcpy(data + size, src, src_size);
            size += src_size;
        }

        void Clear()
        {
            free(data);
            data = nullptr;
            size = buf_size = 0;
        }

        char* data;
        size_t size;
    
    private:
        size_t buf_size;
    };

    typedef shared_ptr<DataBuffer> DataBufferPtr;
}
