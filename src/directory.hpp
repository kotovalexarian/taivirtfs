#pragma once

#include "directory_entry.hpp"

#include <vector>

namespace TaiVirtFS {

class Directory final
{
    std::vector<DirectoryEntry> entries;

public:
    void add_entry(DirectoryEntry &&entry)
    {
        entries.push_back(entry);
    }
};

}
