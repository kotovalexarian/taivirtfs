#pragma once

#include <memory>
#include <sys/types.h>

namespace TaiVirtFS {

class Process final
{
    pid_t pid_;
    uid_t uid_;
    gid_t gid_;

public:
    Process(const pid_t pid, const uid_t uid, const gid_t gid)
        : pid_(pid) , uid_(uid) , gid_(gid)
    {}

    pid_t pid() const { return pid_; }
    uid_t uid() const { return uid_; }
    gid_t gid() const { return gid_; }
};

}
