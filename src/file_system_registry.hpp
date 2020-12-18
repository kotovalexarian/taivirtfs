#pragma once

#include "file_systems/base.hpp"
#include "file_systems/dumbfs.hpp"

#include <memory>
#include <string>

namespace TaiVirtFS {

class FileSystemRegistry final
{
public:
    std::unique_ptr<FileSystems::Base>
    build(const std::string &file_system_type) const
    {
        if (file_system_type == "dumbfs") {
            return std::make_unique<FileSystems::DumbFS>();
        }
        else {
            return std::unique_ptr<FileSystems::Base>(nullptr);
        }
    }
};

}
