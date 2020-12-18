#pragma once

#include "mount_request.hpp"
#include "mounted_file_system.hpp"

#include <string>
#include <vector>

class VirtualFileSystem final
{
    std::vector<MountedFileSystem> mounted_file_systems;
public:
    std::string inspect();
    void mount(const MountRequest &mount_request);
};
