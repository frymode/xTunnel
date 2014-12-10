#pragma once

namespace xTunnel
{
    struct HttpHeader
    {
        string name;
        string value;
    };

    struct HttpRequest
    {
        string method;
        string uri;

        int http_version_major;
        int http_version_minor;
        vector<HttpHeader> headers;
    };

    class HttpRequestParser
    {
    public:
        enum ResultType
        {
            kGood,
            kBad,
            kIndeterminate
        };

        enum State
        {
            method_start,
            method,
            uri,
            http_version_h,
            http_version_t_1,
            http_version_t_2,
            http_version_p,
            http_version_slash,
            http_version_major_start,
            http_version_major,
            http_version_minor_start,
            http_version_minor,
            expecting_newline_1,
            header_line_start,
            header_lws,
            header_name,
            space_before_header_value,
            header_value,
            expecting_newline_2,
            expecting_newline_3
        };

        HttpRequestParser();
        State state() const { return state_; }

        void Reset();
        ResultType Consume(HttpRequest& req, char input);

    private:
        State state_;
    };
}