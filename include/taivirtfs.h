#ifndef _TAIVIRTFS_H
#define _TAIVIRTFS_H 1

#include <linux/ioctl.h>

enum {
    TAIVIRTFS_COMMAND_INSPECT = _IO('E', 0),
    TAIVIRTFS_COMMAND_MOUNT   = _IO('E', 1),
};

struct TaiVirtFS_Command_Mount {
    char target[256];
    char source[256];
    char file_system_type[256];
    unsigned long flags;
};

#endif
