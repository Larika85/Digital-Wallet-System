# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -std=c++11

# Project name and target
TARGET = DigitalWalletSystem

# List of all .cpp files in the directory
SOURCES = $(wildcard *.cpp)

OBJDIR = obj

# Automatically generated list of .o files based on .cpp file names
OBJECTS = $(patsubst %.cpp, $(OBJDIR)/%.o, $(SOURCES))

# Default target
all: $(TARGET)

# Link the executable
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET)

# Compile each .cpp file into .o file
$(OBJDIR)/%.o: %.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

# Rule for creating .o files from .cpp files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean target to remove object files and the executable
clean:
	rm -rf $(OBJECTS) $(TARGET)
	rmdir obj

test:
	@echo "Running tests..."

# Phony targets
.PHONY: all clean