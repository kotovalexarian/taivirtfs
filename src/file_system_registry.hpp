#pragma once

#include "file_systems/base.hpp"
#include "file_systems/dumb.hpp"
#include "file_systems/hello.hpp"

#include <memory>
#include <string>

namespace TaiVirtFS {

class FileSystemRegistry final
{
public:
    std::unique_ptr<FileSystems::Base>
    build(const std::string &file_system_type) const
    {
        if (file_system_type == "dumb") {
            return std::make_unique<FileSystems::Dumb>();
        }
        else if (file_system_type == "hello") {
            return std::make_unique<FileSystems::Hello>();
        }
        else {
            return std::unique_ptr<FileSystems::Base>(nullptr);
        }
    }
};

}
