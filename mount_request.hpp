#pragma once

#include <string>
#include <sys/types.h>

class MountRequest
{
    pid_t pid_;
    uid_t uid_;
    gid_t gid_;

    std::string raw_target_;

public:
    MountRequest(
        const pid_t pid,
        const uid_t uid,
        const gid_t gid,
        const std::string &raw_target
    )
        : pid_(pid)
        , uid_(uid)
        , gid_(gid)
        , raw_target_(raw_target)
    {}

    const std::string &raw_target() const
    {
        return raw_target_;
    }
};
