#pragma once

#include <string>
#include <sys/stat.h>

namespace TaiVirtFS {

class DirectoryEntry final
{
    std::string name_;
    struct stat stat_;

public:
    DirectoryEntry(const std::string &name, struct stat &&stat)
        : name_(name)
        , stat_(stat)
    {}

    std::string name() const
    {
        return name_;
    }

    struct stat stat() const
    {
        return stat_;
    }
};

}
