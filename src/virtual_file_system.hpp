#pragma once

#include "file_system_registry.hpp"
#include "mount_request.hpp"
#include "mounted_file_system.hpp"

#include <string>
#include <vector>

class VirtualFileSystem final
{
    TaiVirtFS::FileSystemRegistry file_system_registry;
    std::vector<MountedFileSystem> mounted_file_systems;
public:
    std::string inspect();
    void mount(const MountRequest &mount_request);
};
