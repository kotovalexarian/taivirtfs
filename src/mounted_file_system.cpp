#include "mounted_file_system.hpp"

std::string MountedFileSystem::inspect() const
{
    std::string result;
    result.append(source_);
    result.append(" on ");
    result.append(target_);
    result.append(" type ");
    result.append(file_system_type_);
    result.append(" (");
    result.append(")");
    return result;
}
