#pragma once

#include <string>

class MountRequest
{
    std::string raw_target_;

public:
    MountRequest(const std::string &raw_target)
        : raw_target_(raw_target)
    {}

    const std::string &raw_target() const
    {
        return raw_target_;
    }
};
