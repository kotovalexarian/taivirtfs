#include "mount_request.hpp"

#include <boost/algorithm/string.hpp>
#include <boost/format.hpp>
#include <string>

struct Escaper
{
    template<class FindResultT>
    std::string operator()(const FindResultT &match) const
    {
        std::string result;
        for (
            typename FindResultT::const_iterator iter = match.begin();
            iter != match.end();
            ++iter
        ) {
            result +=
                (boost::format("\\x%02x") % static_cast<int>(*iter)).str();
        }
        return result;
    }
};

std::string MountRequest::inspect() const
{
    std::string result;
    result.append("MountRequest:\n");
    result.append("  pid: ");
    result.append(std::to_string(pid_));
    result.append("\n");
    result.append("  uid: ");
    result.append(std::to_string(uid_));
    result.append("\n");
    result.append("  gid: ");
    result.append(std::to_string(gid_));
    result.append("\n");
    result.append("  target: ");
    result.append(escaped_target());
    result.append("\n");
    result.append("  source: ");
    result.append(escaped_source());
    result.append("\n");
    result.append("  file system type: ");
    result.append(escaped_file_system_type());
    result.append("\n");
    result.append("  flags: ");
    result.append(std::to_string(flags_));
    result.append("\n");
    return result;
}

std::string MountRequest::escaped_target() const
{
    std::string result(raw_target_);
    boost::find_format_all(
        result,
        boost::token_finder(!boost::is_print()),
        Escaper()
    );
    return result;
}

std::string MountRequest::escaped_source() const
{
    std::string result(raw_source_);
    boost::find_format_all(
        result,
        boost::token_finder(!boost::is_print()),
        Escaper()
    );
    return result;
}

std::string MountRequest::escaped_file_system_type() const
{
    std::string result(raw_file_system_type_);
    boost::find_format_all(
        result,
        boost::token_finder(!boost::is_print()),
        Escaper()
    );
    return result;
}
