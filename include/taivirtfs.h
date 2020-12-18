#ifndef _TAIVIRTFS_H
#define _TAIVIRTFS_H 1

#include <linux/ioctl.h>

enum {
    TAIVIRTFS_COMMAND_INSPECT = _IO('E', 0),
    TAIVIRTFS_COMMAND_MOUNT   = _IO('E', 1),
};

#endif
