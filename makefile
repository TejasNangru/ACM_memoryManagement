# Compiler
CXX = g++
CXXFLAGS = -std=c++17 -Wall

# Output binary
TARGET = memsim

# Source files
SRCS = main.cpp \
       src/memory/memory_manager.cpp \
       src/cli/command_parser.cpp \
       src/cache/cache_level.cpp \
       src/cache/cache_system.cpp

# Default target
all: $(TARGET)

# Build executable
$(TARGET):
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

# Run the simulator
run: $(TARGET)
	./$(TARGET)

# Clean build files
clean:
	rm -f $(TARGET)

.PHONY: all run clean
