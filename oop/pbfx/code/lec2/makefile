CXX      := g++
CXXFLAGS := -Wall -g -std=c++11

SRCS := $(wildcard *.cpp)
BINS := $(SRCS:.cpp=)

all: $(BINS)

%: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

clean:
	rm -f $(BINS)

.PHONY: all clean
