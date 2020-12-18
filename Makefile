CXX = g++

CFLAGS = -Wall -Wextra -Iinclude `pkg-config fuse3 --cflags`
LDFLAGS = `pkg-config fuse3 --libs`

TAIVIRTFS_EXE = taivirtfs
IOCTL_EXE = ioctl
TAIVIRTFS_OBJS = main.o mount_request.o virtual_file_system.o
IOCTL_OBJS = ioctl.o

TAIVIRTFS_OBJ_PATHS = $(addprefix src/, $(TAIVIRTFS_OBJS))
IOCTL_OBJ_PATHS     = $(addprefix src/, $(IOCTL_OBJS))

all: $(TAIVIRTFS_EXE) $(IOCTL_EXE)

clean:
	rm -f $(TAIVIRTFS_EXE) $(IOCTL_EXE) $(TAIVIRTFS_OBJ_PATHS) $(IOCTL_OBJ_PATHS)

$(TAIVIRTFS_EXE): $(TAIVIRTFS_OBJ_PATHS)
	$(CXX) -o $@ $^ $(LDFLAGS)

$(IOCTL_EXE): $(IOCTL_OBJ_PATHS)
	$(CXX) -o $@ $^ $(LDFLAGS)

src/%.o: src/%.cpp
	$(CXX) -c $< -o $@ $(CFLAGS)
