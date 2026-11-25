CXX ?= g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra
LDLIBS ?= -lncurses

roguelike: $(wildcard *.cpp *.hpp)
	$(CXX) $(CXXFLAGS) main.cpp -o $@ $(LDLIBS)

.PHONY: clean
clean:
	rm -f roguelike
