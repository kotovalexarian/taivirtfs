#include <errno.h>

#define FUSE_USE_VERSION 31
#include <cuse_lowlevel.h>
#include <fuse_opt.h>

enum class Command {
    Inspect = 1,
};

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
    const void *const in_buf __attribute__((unused)),
    const size_t in_buf_size __attribute__((unused)),
    const size_t out_buf_size __attribute__((unused))
) {
    if (flags & FUSE_IOCTL_COMPAT) {
        fuse_reply_err(req, ENOSYS);
        return;
    }

    switch (cmd) {
    case int(Command::Inspect):
        {
            if (out_buf_size == 0) {
                struct iovec out_iov = { arg, 14 };
                fuse_reply_ioctl_retry(req, nullptr, 0, &out_iov, 1);
            }
            else {
                static const char hello_world[] = "Hello, World!";
                fuse_reply_ioctl(req, 0, hello_world, 14);
            }
        }
        break;
    default:
        fuse_reply_err(req, EINVAL);
    }
}
