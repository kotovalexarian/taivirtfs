#pragma once

#include "file_systems/base.hpp"

#include <string>

class MountedFileSystem final
{
    std::string target_;
    std::string source_;
    std::string file_system_type_;
    TaiVirtFS::FileSystems::Base file_system_;

public:
    MountedFileSystem(
        const std::string &target,
        const std::string &source,
        const std::string &file_system_type,
        TaiVirtFS::FileSystems::Base &&file_system
    )
        : target_(target)
        , source_(source)
        , file_system_type_(file_system_type)
        , file_system_(file_system)
    {}

    std::string inspect() const;

    const std::string &target() const
    {
        return target_;
    }

    const std::string &source() const
    {
        return source_;
    }

    const std::string &file_system_type() const
    {
        return file_system_type_;
    }
};
