#pragma once

#include "../directory.hpp"

#include <string>

namespace TaiVirtFS {
namespace FileSystems {

class Base
{
public:
    virtual int
    read_dir(const std::string &path, Directory &directory) const = 0;
};

}
}
