CXX = g++

CFLAGS = -Wall -Wextra `pkg-config fuse3 --cflags`
LDFLAGS = `pkg-config fuse3 --libs`

EXE = taivirtfs
OBJS = main.o virtual_file_system.o

all: $(EXE)

clean:
	rm -f $(EXE) $(OBJS)

$(EXE): $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) -c $< -o $@ $(CFLAGS)
