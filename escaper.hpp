#pragma once

#include <boost/format.hpp>

struct Escaper
{
    template<class FindResultT>
    std::string operator()(const FindResultT &match) const
    {
        std::string result;
        for (
            typename FindResultT::const_iterator iter = match.begin();
            iter != match.end();
            ++iter
        ) {
            result +=
                (boost::format("\\x%02x") % static_cast<int>(*iter)).str();
        }
        return result;
    }
};
