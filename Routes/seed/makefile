# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++17 -Wall -Wextra -Wreorder -g

# Linker flags for libraries
LDFLAGS = -lmariadbcpp -lcgicc -lcrypto++

# Source files
SOURCES = 	seed.cpp \
			../../Logger/logger.cpp \
			../../Controllers/Seeding/seed.cpp \
			../../Views/views.cpp \
			../../Views/sections/seed/seed.view.cpp \
			../../Views/components/header.comp.cpp \
			../../Views/components/csrf_token.comp.cpp \
			../../Helpers/Database/db_connection.cpp \
			../../Helpers/Cryptography/crypto.cpp \
			../../Helpers/Database/Users/users.cpp \
			../../Helpers/Session/session.cpp \
			../../Helpers/String/string_helpers.cpp \
			../../Helpers/Request/requests.cpp \
			
# Object files
OBJECTS = $(SOURCES:.cpp=.o)

# Executable name
EXECUTABLE = seed.cgi

# Default target
all: $(EXECUTABLE)

# Rule to link the program
$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) $(LDFLAGS) -o $@

# Rule to compile source files to object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean target
clean:
	rm -f $(OBJECTS) $(EXECUTABLE)

# Phony targets
.PHONY: all clean