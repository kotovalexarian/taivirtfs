#pragma once

#include "file_systems/base.hpp"
#include "file_systems/dumbfs.hpp"

#include <optional>
#include <string>

namespace TaiVirtFS {

class FileSystemRegistry final
{
public:
    std::optional<FileSystems::Base>
    build(const std::string &file_system_type) const
    {
        if (file_system_type == "dumbfs") {
            return std::optional(FileSystems::DumbFS());
        }
        else {
            return std::optional<FileSystems::Base>();
        }
    }
};

}
