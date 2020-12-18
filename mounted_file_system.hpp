#pragma once

#include <string>

class MountedFileSystem final
{
    std::string target_;
public:
    MountedFileSystem(const std::string &target)
        : target_(target)
    {}

    const std::string &target() const
    {
        return target_;
    }
};
