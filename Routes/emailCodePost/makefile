# Include common configurations
include ../../common.mk

# Unique source file
SOURCES = emailCodePost.cpp $(COMMON_SOURCES)

# Object files
OBJECTS = $(SOURCES:.cpp=.o)

# Executable name
EXECUTABLE = emailCodePost.cgi

# Default target
all: $(EXECUTABLE)

# Rule to link the program
$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) $(LDFLAGS) -o $@
