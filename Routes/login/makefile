# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++17 -Wall -Wextra -Wreorder -g

# Dependencies
LIBRARIES = -lmariadbcpp -lcgicc

# Linker flags for libraries
LDFLAGS = -lmariadbcpp -lcgicc

# Source files
SOURCES = 	login.cpp \
			../../Views/sections/login/login.view.cpp

# Object files
OBJECTS = $(SOURCES:.cpp=.o)

# Executable name
EXECUTABLE = login.cgi

# Default target
all: $(EXECUTABLE)

# Rule to link the program
$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) $(LIBRARIES) -o $@

# Rule to compile source files to object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean target
clean:
	rm -f $(OBJECTS) $(EXECUTABLE)

# Phony targets
.PHONY: all clean