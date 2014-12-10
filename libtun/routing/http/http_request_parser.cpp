#include "stdafx.h"
#include "http_request_parser.h"

namespace xTunnel
{
    namespace
    {
        bool is_char(int c)
        {
            return c >= 0 && c <= 127;
        }

        bool is_ctl(int c)
        {
            return (c >= 0 && c <= 31) || (c == 127);
        }

        bool is_tspecial(int c)
        {
            switch (c)
            {
            case '(': case ')': case '<': case '>': case '@':
            case ',': case ';': case ':': case '\\': case '"':
            case '/': case '[': case ']': case '?': case '=':
            case '{': case '}': case ' ': case '\t':
                return true;
            default:
                return false;
            }
        }

        bool is_digit(int c)
        {
            return c >= '0' && c <= '9';
        }
    }

    HttpRequestParser::HttpRequestParser()
        : state_(method_start)
    {
    }

    void HttpRequestParser::Reset()
    {
        state_ = method_start;
    }

    HttpRequestParser::ResultType HttpRequestParser::Consume(HttpRequest& req, char input)
    {
        switch (state_)
        {
        case method_start:
            if (!is_char(input) || is_ctl(input) || is_tspecial(input))
            {
                return kBad;
            }
            else
            {
                state_ = method;
                req.method.push_back(input);
                return kIndeterminate;
            }
        case method:
            if (input == ' ')
            {
                state_ = uri;
                return kIndeterminate;
            }
            else if (!is_char(input) || is_ctl(input) || is_tspecial(input))
            {
                return kBad;
            }
            else
            {
                req.method.push_back(input);
                return kIndeterminate;
            }
        case uri:
            if (input == ' ')
            {
                state_ = http_version_h;
                return kIndeterminate;
            }
            else if (is_ctl(input))
            {
                return kBad;
            }
            else
            {
                req.uri.push_back(input);
                return kIndeterminate;
            }
        case http_version_h:
            if (input == 'H')
            {
                state_ = http_version_t_1;
                return kIndeterminate;
            }
            else
            {
                return kBad;
            }
        case http_version_t_1:
            if (input == 'T')
            {
                state_ = http_version_t_2;
                return kIndeterminate;
            }
            else
            {
                return kBad;
            }
        case http_version_t_2:
            if (input == 'T')
            {
                state_ = http_version_p;
                return kIndeterminate;
            }
            else
            {
                return kBad;
            }
        case http_version_p:
            if (input == 'P')
            {
                state_ = http_version_slash;
                return kIndeterminate;
            }
            else
            {
                return kBad;
            }
        case http_version_slash:
            if (input == '/')
            {
                req.http_version_major = 0;
                req.http_version_minor = 0;
                state_ = http_version_major_start;
                return kIndeterminate;
            }
            else
            {
                return kBad;
            }
        case http_version_major_start:
            if (is_digit(input))
            {
                req.http_version_major = req.http_version_major * 10 + input - '0';
                state_ = http_version_major;
                return kIndeterminate;
            }
            else
            {
                return kBad;
            }
        case http_version_major:
            if (input == '.')
            {
                state_ = http_version_minor_start;
                return kIndeterminate;
            }
            else if (is_digit(input))
            {
                req.http_version_major = req.http_version_major * 10 + input - '0';
                return kIndeterminate;
            }
            else
            {
                return kBad;
            }
        case http_version_minor_start:
            if (is_digit(input))
            {
                req.http_version_minor = req.http_version_minor * 10 + input - '0';
                state_ = http_version_minor;
                return kIndeterminate;
            }
            else
            {
                return kBad;
            }
        case http_version_minor:
            if (input == '\r')
            {
                state_ = expecting_newline_1;
                return kIndeterminate;
            }
            else if (is_digit(input))
            {
                req.http_version_minor = req.http_version_minor * 10 + input - '0';
                return kIndeterminate;
            }
            else
            {
                return kBad;
            }
        case expecting_newline_1:
            if (input == '\n')
            {
                state_ = header_line_start;
                return kIndeterminate;
            }
            else
            {
                return kBad;
            }
        case header_line_start:
            if (input == '\r')
            {
                state_ = expecting_newline_3;
                return kIndeterminate;
            }
            else if (!req.headers.empty() && (input == ' ' || input == '\t'))
            {
                state_ = header_lws;
                return kIndeterminate;
            }
            else if (!is_char(input) || is_ctl(input) || is_tspecial(input))
            {
                return kBad;
            }
            else
            {
                req.headers.push_back(HttpHeader());
                req.headers.back().name.push_back(input);
                state_ = header_name;
                return kIndeterminate;
            }
        case header_lws:
            if (input == '\r')
            {
                state_ = expecting_newline_2;
                return kIndeterminate;
            }
            else if (input == ' ' || input == '\t')
            {
                return kIndeterminate;
            }
            else if (is_ctl(input))
            {
                return kBad;
            }
            else
            {
                state_ = header_value;
                req.headers.back().value.push_back(input);
                return kIndeterminate;
            }
        case header_name:
            if (input == ':')
            {
                state_ = space_before_header_value;
                return kIndeterminate;
            }
            else if (!is_char(input) || is_ctl(input) || is_tspecial(input))
            {
                return kBad;
            }
            else
            {
                req.headers.back().name.push_back(input);
                return kIndeterminate;
            }
        case space_before_header_value:
            if (input == ' ')
            {
                state_ = header_value;
                return kIndeterminate;
            }
            else
            {
                return kBad;
            }
        case header_value:
            if (input == '\r')
            {
                state_ = expecting_newline_2;
                return kIndeterminate;
            }
            else if (is_ctl(input))
            {
                return kBad;
            }
            else
            {
                req.headers.back().value.push_back(input);
                return kIndeterminate;
            }
        case expecting_newline_2:
            if (input == '\n')
            {
                state_ = header_line_start;
                return kIndeterminate;
            }
            else
            {
                return kBad;
            }
        case expecting_newline_3:
            return (input == '\n') ? kGood : kBad;
        default:
            return kBad;
        }
    }
}