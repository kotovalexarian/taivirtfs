#include "virtual_file_system.hpp"

#include <iostream>

std::string VirtualFileSystem::inspect()
{
    std::string result;

    if (mounts.size() == 0) {
        result.append("0 mounts.\n");
    }
    else {
        result.append(std::to_string(mounts.size()));
        result.append(" mounts:\n");

        for (const auto &mount : mounts) {
            result.append("  ");
            result.append(mount);
            result.append("\n");
        }
    }

    return result;
}
