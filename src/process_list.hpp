#pragma once

#include "process.hpp"

#include <exception>
#include <sys/types.h>
#include <vector>

namespace TaiVirtFS {

class ProcessList final
{
    std::vector<Process> processes_;

public:
    const std::vector<Process> &processes() const { return processes_; }

    void fork(const pid_t parent_pid, const pid_t child_pid)
    {
        for (Process &process : processes_) {
            if (process.pid() == child_pid) {
                throw std::logic_error("Child PID already exists");
            }
        }

        for (Process &process : processes_) {
            if (process.pid() == parent_pid) {
                processes_.push_back(process.fork(child_pid));
                return;
            }
        }

        throw std::logic_error("Parent PID doesn't exist");
    }
};

}
