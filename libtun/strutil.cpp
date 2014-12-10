#include "stdafx.h"
#include "strutil.h"

namespace xTunnel
{
    namespace
    {
        const char* tbl_cp1251_utf8[] =
        {
            "\xd0\x82", "\xd0\x83", "\xe2\x80\x9a", "\xd1\x93", "\xe2\x80\x9e", "\xe2\x80\xa6", "\xe2\x80\xa0",
            "\xe2\x80\xa1", "\xe2\x82\xac", "\xe2\x80\xb0", "\xd0\x89", "\xe2\x80\xb9", "\xd0\x8a", "\xd0\x8c",
            "\xd0\x8b", "\xd0\x8f", "\xd1\x92", "\xe2\x80\x98", "\xe2\x80\x99", "\xe2\x80\x9c", "\xe2\x80\x9d",
            "\xe2\x80\xa2", "\xe2\x80\x93", "\xe2\x80\x94", "\xc2\x98", "\xe2\x84\xa2", "\xd1\x99", "\xe2\x80\xba",
            "\xd1\x9a", "\xd1\x9c", "\xd1\x9b", "\xd1\x9f", "\xc2\xa0", "\xd0\x8e", "\xd1\x9e", "\xd0\x88",
            "\xc2\xa4", "\xd2\x90", "\xc2\xa6", "\xc2\xa7", "\xd0\x81", "\xc2\xa9", "\xd0\x84", "\xc2\xab",
            "\xc2\xac", "\xc2\xad", "\xc2\xae", "\xd0\x87", "\xc2\xb0", "\xc2\xb1", "\xd0\x86", "\xd1\x96",
            "\xd2\x91", "\xc2\xb5", "\xc2\xb6", "\xc2\xb7", "\xd1\x91", "\xe2\x84\x96", "\xd1\x94", "\xc2\xbb",
            "\xd1\x98", "\xd0\x85", "\xd1\x95", "\xd1\x97", "\xd0\x90", "\xd0\x91", "\xd0\x92", "\xd0\x93",
            "\xd0\x94", "\xd0\x95", "\xd0\x96", "\xd0\x97", "\xd0\x98", "\xd0\x99", "\xd0\x9a", "\xd0\x9b",
            "\xd0\x9c", "\xd0\x9d", "\xd0\x9e", "\xd0\x9f", "\xd0\xa0", "\xd0\xa1", "\xd0\xa2", "\xd0\xa3",
            "\xd0\xa4", "\xd0\xa5", "\xd0\xa6", "\xd0\xa7", "\xd0\xa8", "\xd0\xa9", "\xd0\xaa", "\xd0\xab",
            "\xd0\xac", "\xd0\xad", "\xd0\xae", "\xd0\xaf", "\xd0\xb0", "\xd0\xb1", "\xd0\xb2", "\xd0\xb3",
            "\xd0\xb4", "\xd0\xb5", "\xd0\xb6", "\xd0\xb7", "\xd0\xb8", "\xd0\xb9", "\xd0\xba", "\xd0\xbb",
            "\xd0\xbc", "\xd0\xbd", "\xd0\xbe", "\xd0\xbf", "\xd1\x80", "\xd1\x81", "\xd1\x82", "\xd1\x83",
            "\xd1\x84", "\xd1\x85", "\xd1\x86", "\xd1\x87", "\xd1\x88", "\xd1\x89", "\xd1\x8a", "\xd1\x8b",
            "\xd1\x8c", "\xd1\x8d", "\xd1\x8e", "\xd1\x8f"
        };

        inline void char_to_hex(char c, char* buf)
        {
            static const char hex_char[] = "0123456789ABCDEF";

            buf[0] = hex_char[(c >> 4) & 0x0f];
            buf[1] = hex_char[c & 0x0f];
        }

        struct is_space_pred
        {
            inline bool operator ()(char c) const
            {
                return c == ' ';
            }
        };

        static const is_space_pred is_space_pred_instance;
    }

    string bytes_to_string(const char* data, size_t size)
    {
        char hex_buf[2];

        string res(data, size);
        for (size_t i = 0, p = 0; i < size; ++i, ++p)
        {
            char c = data[i];
            if (c < 0x20 || c == 0x7F || c == 0xFF)
            {
                char_to_hex(c, hex_buf);
                res[p] = '%';
                res.insert(p + 1, hex_buf, 2);
                p += 2;
            }
        }

        return res;
    }

    string bytes_as_hex(const char* data, size_t size)
    {
        string str(size * 2, ' ');
        char* str_data = (char*)str.data();
        for (size_t i = 0; i < size; ++i)
        {
            char_to_hex(data[i], str_data + i * 2);
        }

        return str;
    }

    string PadLeft(int size, const string& value, char padding /*= ' '*/)
    {
        int len = value.length();
        int pad_len = size - len;

        if (pad_len > 0)
        {
            return string(pad_len, padding) + value;
        }
        else
        {
            return value;
        }
    }

    string PadLeft(int size, const string* value /*= NULL*/, char padding /*= ' '*/)
    {
        if (value)
        {
            return PadLeft(size, *value, padding);
        }
        else
        {
            return string(size, padding);
        }
    }

    string PadRight(int size, const string& value, char padding /*= ' '*/)
    {
        int len = value.length();
        int pad_len = size - len;

        if (pad_len > 0)
        {
            return value + string(pad_len, padding);
        }
        else
        {
            return value;
        }
    }

    string PadRight(int size, const string* value /*= NULL*/, char padding /*= ' '*/)
    {
        if (value)
        {
            return PadRight(size, *value, padding);
        }
        else
        {
            return string(size, padding);
        }
    }

    string TrimRight(const string& s)
    {
        const char* sbegin = s.c_str();
        const char* spos = sbegin + s.length() - 1;

        for ( ; spos >= sbegin; --spos)
        {
            if (*spos != ' ')
            {
                break;
            }
        }

        return string(sbegin, spos + 1);
    }

    vector<string> split(const string& s, const string& tokens)
    {
        vector<string> res;
        split(res, s, is_any_of(tokens), token_compress_on);
        return res;
    }
}