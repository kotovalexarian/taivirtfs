#include "virtual_file_system.hpp"

#include <iostream>

std::string VirtualFileSystem::inspect()
{
    std::string result;

    if (mounted_file_systems.size() == 0) {
        result.append("0 mounts.\n");
    }
    else {
        result.append(std::to_string(mounted_file_systems.size()));
        result.append(" mounts:\n");

        for (const auto &mount : mounted_file_systems) {
            result.append("  ");
            result.append(mount.target());
            result.append("\n");
        }
    }

    return result;
}

void VirtualFileSystem::mount(const MountRequest &mount_request)
{
    MountedFileSystem mounted_file_system(
        mount_request.raw_target(),
        mount_request.raw_source()
    );

    mounted_file_systems.push_back(mounted_file_system);
}
