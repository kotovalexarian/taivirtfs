#include <taivirtfs.h>
#include "mount_request.hpp"
#include "virtual_file_system.hpp"

#include <iostream>

#include <errno.h>

#define FUSE_USE_VERSION 31
#include <cuse_lowlevel.h>
#include <fuse_opt.h>

static VirtualFileSystem virtual_file_system;

static std::string virtual_file_system_inspect;

static const char *dev_info_argv[] = { "DEVNAME=taivirtfs" };

static const struct cuse_info cuse_info = {
    .dev_major = 123,
    .dev_minor = 123,
    .dev_info_argc = 1,
    .dev_info_argv = dev_info_argv,
    .flags = CUSE_UNRESTRICTED_IOCTL,
};

static void on_open(fuse_req_t req, struct fuse_file_info *file_info);

static void on_read(
    fuse_req_t req,
    size_t size,
    off_t off,
    struct fuse_file_info *file_info
);

static void on_write(
    fuse_req_t req,
    const char *buf,
    size_t size,
    off_t off,
    struct fuse_file_info *file_info
);

static void on_ioctl(
    fuse_req_t req,
    int cmd,
    void *arg,
    struct fuse_file_info *file_info,
    unsigned flags,
    const void *in_buf,
    size_t in_buf_size,
    size_t out_buf_size
);

static const struct cuse_lowlevel_ops cuse_lowlevel_ops = {
    .init      = nullptr,
    .init_done = nullptr,
    .destroy   = nullptr,
    .open      = on_open,
    .read      = on_read,
    .write     = on_write,
    .flush     = nullptr,
    .release   = nullptr,
    .fsync     = nullptr,
    .ioctl     = on_ioctl,
    .poll      = nullptr,
};

int main(int argc, char **argv)
{
    struct fuse_args args = FUSE_ARGS_INIT(argc, argv);

    if (fuse_opt_parse(&args, nullptr, nullptr, nullptr) == -1) return 1;

    const int result = cuse_lowlevel_main(
        args.argc,
        args.argv,
        &cuse_info,
        &cuse_lowlevel_ops,
        nullptr
    );

    fuse_opt_free_args(&args);

    return result;
}

void on_open(fuse_req_t req, struct fuse_file_info *const file_info)
{
    fuse_reply_open(req, file_info);
}

void on_read(
    fuse_req_t req,
    const size_t size __attribute__((unused)),
    const off_t off __attribute__((unused)),
    struct fuse_file_info *file_info __attribute__((unused))
) {
    fuse_reply_buf(req, nullptr, 0);
}

void on_write(
    fuse_req_t req,
    const char *buf __attribute__((unused)),
    size_t size,
    off_t off __attribute__((unused)),
    struct fuse_file_info *file_info __attribute__((unused))
) {
    fuse_reply_write(req, size);
}

void on_ioctl(
    fuse_req_t req,
    const int cmd,
    void *const arg,
    struct fuse_file_info *const file_info __attribute__((unused)),
    const unsigned flags,
    const void *const in_buf,
    const size_t in_buf_size,
    const size_t out_buf_size
) {
    const struct fuse_ctx *const ctx = fuse_req_ctx(req);

    if (flags & FUSE_IOCTL_COMPAT) {
        fuse_reply_err(req, ENOSYS);
        return;
    }

    switch (cmd) {
    case TAIVIRTFS_COMMAND_INSPECT:
        {
            if (out_buf_size == 0) {
                virtual_file_system_inspect = virtual_file_system.inspect();

                struct iovec out_iov = {
                    arg,
                    virtual_file_system_inspect.size()
                };

                fuse_reply_ioctl_retry(req, nullptr, 0, &out_iov, 1);
            }
            else {
                fuse_reply_ioctl(
                    req,
                    0,
                    virtual_file_system_inspect.c_str(),
                    virtual_file_system_inspect.size()
                );
            }
        }
        break;
    case TAIVIRTFS_COMMAND_MOUNT:
        {
            if (in_buf_size == 0) {
                const struct iovec in_iov[4] = {
                    {
                        .iov_base = arg + offsetof(
                            struct TaiVirtFS_Command_Mount,
                            target
                        ),
                        .iov_len = sizeof(char[256]),
                    },
                    {
                        .iov_base = arg + offsetof(
                            struct TaiVirtFS_Command_Mount,
                            source
                        ),
                        .iov_len = sizeof(char[256]),
                    },
                    {
                        .iov_base = arg + offsetof(
                            struct TaiVirtFS_Command_Mount,
                            file_system_type
                        ),
                        .iov_len = sizeof(char[256]),
                    },
                    {
                        .iov_base = arg + offsetof(
                            struct TaiVirtFS_Command_Mount,
                            flags
                        ),
                        .iov_len = sizeof(unsigned long),
                    }
                };

                fuse_reply_ioctl_retry(req, in_iov, 4, nullptr, 0);
            }
            else {
                const struct TaiVirtFS_Command_Mount *const args =
                    static_cast<const struct TaiVirtFS_Command_Mount*>(in_buf);

                MountRequest mount_request(
                    ctx->pid,
                    ctx->uid,
                    ctx->gid,
                    args->target,
                    args->source,
                    args->file_system_type,
                    args->flags
                );

                std::cout << mount_request.inspect();

                int result = virtual_file_system.mount(mount_request);
                fuse_reply_ioctl(req, result, nullptr, 0);
            }
        }
        break;
    default:
        fuse_reply_err(req, EINVAL);
    }
}
