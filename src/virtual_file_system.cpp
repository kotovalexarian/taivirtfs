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

        for (const auto &mounted_file_system : mounted_file_systems) {
            result.append("  ");
            result.append(mounted_file_system.inspect());
            result.append("\n");
        }
    }

    return result;
}

void VirtualFileSystem::mount(const MountRequest &mount_request)
{
    std::optional<TaiVirtFS::FileSystems::Base> file_system =
        file_system_registry.build(mount_request.raw_file_system_type());

    if (!file_system) return;

    MountedFileSystem mounted_file_system(
        mount_request.raw_target(),
        mount_request.raw_source(),
        mount_request.raw_file_system_type(),
        std::move(file_system.value())
    );

    mounted_file_systems.push_back(mounted_file_system);
}
