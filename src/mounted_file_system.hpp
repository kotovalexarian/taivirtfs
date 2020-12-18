#pragma once

#include <string>

class MountedFileSystem final
{
    std::string target_;
    std::string source_;
    std::string file_system_type_;

public:
    MountedFileSystem(
        const std::string &target,
        const std::string &source,
        const std::string &file_system_type
    )
        : target_(target)
        , source_(source)
        , file_system_type_(file_system_type)
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
