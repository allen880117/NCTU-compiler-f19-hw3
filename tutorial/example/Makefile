CXX = g++
CFLAGS = -Wall -std=c++11


bin = main.out

.PHONY: clean

all: $(bin)

$(bin): main.cpp animal.o sound_visitor.o
	$(CXX) $(CFLAGS) $^ -o $@ && ./$@

animal.o: animal.cpp animal.hpp
	$(CXX) $(CFLAGS) -c $< -o $@

sound_visitor.o : sound_visitor.cpp animal.hpp
	$(CXX) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(bin) *.out *.o
