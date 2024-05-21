CXX = g++
CXXFLAGS = -std=c++17 -Wall
CXXTESTFLAGS = --coverage
CXXGDB = -ggdb

# Define the executables
MAIN_EXEC = main
# TEST_EXEC = test

# Define all source files
SOURCES = Driver.cpp User.cpp Product.cpp
# Define all object files
OBJECTS = $(SOURCES:.cpp=.o)

# Default target
all: $(MAIN_EXEC)

# Main game executable
$(MAIN_EXEC): $(OBJECTS) main.o
	$(CXX) $(CXXFLAGS) $(CXXGDB) $^ -o $@

# Test executable
# $(TEST_EXEC): $(OBJECTS) test.o
# 	$(CXX) $(CXXFLAGS) $(CXXTESTFLAGS) $^ -o $@

# Rule for creating object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up the build
clean:
	del -f $(OBJECTS) main.o $(MAIN_EXEC) 

#$ test.o (TEST_EXEC)

# Phony targets for commands that don't represent actual files
.PHONY: all clean
