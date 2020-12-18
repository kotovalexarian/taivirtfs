#ifndef _TAIVIRTFS_H
#define _TAIVIRTFS_H 1

#include <linux/ioctl.h>

enum {
    TAIVIRTFS_COMMAND_INSPECT = _IO('T', 0),
    TAIVIRTFS_COMMAND_MOUNT   = _IO('T', 1),
};

#endif
