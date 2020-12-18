CXX = g++

CFLAGS = -Wall -Wextra -Iinclude `pkg-config fuse3 --cflags`
LDFLAGS = `pkg-config fuse3 --libs`

TAIVIRTFS_EXE = taivirtfs
IOCTL_EXE = ioctl
TAIVIRTFS_OBJS = main.o mount_request.o virtual_file_system.o
IOCTL_OBJS = ioctl.o

all: $(TAIVIRTFS_EXE) $(IOCTL_EXE)

clean:
	rm -f $(TAIVIRTFS_EXE) $(IOCTL_EXE) $(TAIVIRTFS_OBJS) $(IOCTL_OBJS)

$(TAIVIRTFS_EXE): $(TAIVIRTFS_OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS)

$(IOCTL_EXE): $(IOCTL_OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) -c $< -o $@ $(CFLAGS)
