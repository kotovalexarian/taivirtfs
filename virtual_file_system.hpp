#pragma once

#include <string>
#include <vector>

class VirtualFileSystem final
{
    std::vector<std::string> mounts;
public:
    std::string inspect();
    void mount(const std::string &target);
};
