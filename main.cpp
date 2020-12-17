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

static const struct cuse_lowlevel_ops cuse_lowlevel_ops = {
    .init = nullptr,
    .init_done = nullptr,
    .destroy = nullptr,
    .open = nullptr,
    .read = nullptr,
    .write = nullptr,
    .flush = nullptr,
    .release = nullptr,
    .fsync = nullptr,
    .ioctl = nullptr,
    .poll = nullptr,
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
