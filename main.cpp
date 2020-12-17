#define FUSE_USE_VERSION 31
#include <cuse_lowlevel.h>
#include <fuse_opt.h>

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

static void on_flush(fuse_req_t req, struct fuse_file_info *file_info);

static void on_release(fuse_req_t req, struct fuse_file_info *file_info);

static void on_fsync(
    fuse_req_t req,
    int datasync,
    struct fuse_file_info *file_info
);

static void on_poll(
    fuse_req_t req,
    struct fuse_file_info *file_info,
    struct fuse_pollhandle *poll_handle
);

static const struct cuse_lowlevel_ops cuse_lowlevel_ops = {
    .init      = nullptr,
    .init_done = nullptr,
    .destroy   = nullptr,
    .open      = on_open,
    .read      = on_read,
    .write     = on_write,
    .flush     = on_flush,
    .release   = on_release,
    .fsync     = on_fsync,
    .ioctl     = nullptr,
    .poll      = on_poll,
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

void on_flush(
    fuse_req_t req,
    struct fuse_file_info *const file_info __attribute__((unused))
) {
    fuse_reply_err(req, 0);
}

void on_release(
    fuse_req_t req,
    struct fuse_file_info *const file_info __attribute__((unused))
) {
    fuse_reply_err(req, 0);
}

void on_fsync(
    fuse_req_t req,
    const int datasync __attribute__((unused)),
    struct fuse_file_info *const file_info __attribute__((unused))
) {
    fuse_reply_err(req, 0);
}

static void on_poll(
    fuse_req_t req,
    struct fuse_file_info *file_info __attribute__((unused)),
    struct fuse_pollhandle *poll_handle __attribute__((unused))
) {
    fuse_reply_err(req, 0);
}
