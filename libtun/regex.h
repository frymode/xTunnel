#pragma once

#include <boost/regex.hpp>

namespace xutil
{
    typedef boost::regex Regex;
    typedef boost::match_results<string::const_iterator> MatchResults;

    using boost::regex_search;
}
