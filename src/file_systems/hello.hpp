#pragma once

#include "base.hpp"

#include <cerrno>
#include <cstring>

namespace TaiVirtFS {
namespace FileSystems {

class Hello : public Base
{
public:
    int read_dir(const std::string &path, Directory &directory) const override
    {
        if (path != "/") {
            return ENOENT;
        }

        struct stat stat1;
        struct stat stat2;
        struct stat stat3;

        memset(&stat1, 0, sizeof(stat1));
        memset(&stat2, 0, sizeof(stat2));
        memset(&stat3, 0, sizeof(stat3));

        DirectoryEntry directory_entry1(".",     std::move(stat1));
        DirectoryEntry directory_entry2("..",    std::move(stat2));
        DirectoryEntry directory_entry3("hello", std::move(stat3));

        directory.add_entry(std::move(directory_entry1));
        directory.add_entry(std::move(directory_entry2));
        directory.add_entry(std::move(directory_entry3));

        return 0;
    }
};

}
}
