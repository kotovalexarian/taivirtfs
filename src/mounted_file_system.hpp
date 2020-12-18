#pragma once

#include <string>

class MountedFileSystem final
{
    std::string target_;
    std::string source_;

public:
    MountedFileSystem(
        const std::string &target,
        const std::string &source
    )
        : target_(target)
        , source_(source)
    {}

    const std::string &target() const
    {
        return target_;
    }

    const std::string &source() const
    {
        return source_;
    }
};
