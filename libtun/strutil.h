#pragma once

#include <boost/algorithm/string.hpp>

#define FORMAT_STR(fmt, args) str(format(fmt) % args)

namespace xTunnel
{
    using boost::split;
    using boost::token_compress_on;
    using boost::token_compress_off;
    using boost::replace_all;
    using boost::is_any_of;

    vector<string> split(const string& s, const string& tokens);

    inline bool string_ends_with(const string& str, const string& ending)
    {
        if (str.length() < ending.length())
        {
            return false;
        }
        return str.compare(str.length() - ending.length(), ending.length(), ending) == 0;
    }

    string bytes_to_string(const char* data, size_t size);
    string bytes_as_hex(const char* data, size_t size);

    string PadLeft(int size, const string& value, char padding = ' ');
    string PadLeft(int size, const string* value = NULL, char padding = ' ');
    string PadRight(int size, const string& value, char padding = ' ');
    string PadRight(int size, const string* value = NULL, char padding = ' ');

    string TrimRight(const string& s);
}
