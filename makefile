# Makefile for building a shared library

# Compiler
CXX := g++

# Compiler flags
CXXFLAGS := -shared -fPIC -std=c++11

# Source file
SRC := rivector/src/vectors.cpp

# Output library name
TARGET := rivector/lib/vectors.so

# Default target
all: $(TARGET)

# Rule to build the shared library
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $<

# Clean rule
clean:
	rm -f $(TARGET)
