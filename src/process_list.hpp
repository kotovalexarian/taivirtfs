#pragma once

#include "process.hpp"

#include <vector>

namespace TaiVirtFS {

class ProcessList final
{
    std::vector<Process> processes_;

public:
    const std::vector<Process> &processes() const { return processes_; }
};

}
