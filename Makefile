CXX = g++

EXE = taivirtfs

OBJS = main.o

$(EXE): $(OBJS)
	$(CXX) -o $@ $^

%.o: %.cpp
	$(CXX) -c $< -o $@
