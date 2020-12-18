#pragma once

#include <string>
#include <sys/types.h>

class MountRequest
{
    pid_t pid_;
    uid_t uid_;
    gid_t gid_;

    std::string raw_target_;
    std::string raw_source_;
    std::string raw_file_system_type_;
    unsigned long flags_;

public:
    MountRequest(
        const pid_t pid,
        const uid_t uid,
        const gid_t gid,
        const std::string &raw_target,
        const std::string &raw_source,
        const std::string &raw_file_system_type,
        const unsigned long flags
    )
        : pid_(pid)
        , uid_(uid)
        , gid_(gid)
        , raw_target_(raw_target)
        , raw_source_(raw_source)
        , raw_file_system_type_(raw_file_system_type)
        , flags_(flags)
    {}

    pid_t pid() const
    {
        return pid_;
    }

    uid_t uid() const
    {
        return uid_;
    }

    gid_t gid() const
    {
        return gid_;
    }

    const std::string &raw_target() const
    {
        return raw_target_;
    }

    const std::string &raw_source() const
    {
        return raw_source_;
    }

    const std::string &raw_file_system_type() const
    {
        return raw_file_system_type_;
    }

    unsigned long flags() const
    {
        return flags_;
    }
};
