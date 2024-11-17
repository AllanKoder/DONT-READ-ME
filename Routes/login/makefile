# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++17 -Wall -Wextra -Wreorder -g

# Linker flags for libraries
LDFLAGS = -lmariadbcpp -lcgicc -lcrypto++

# Source files
SOURCES = 	login.cpp \
			../../Views/sections/login/login.view.cpp \
			../../Views/views.cpp \
			../../Views/components/header.comp.cpp \
			../../Logger/logger.cpp \
			../../Views/redirect.cpp \
			../../Helpers/Database/db_connection.cpp \
			../../Helpers/Cryptography/crypto.cpp \
			../../Controllers/Login/login.cpp \
			../../Helpers/Session/session.cpp \
			../../Helpers/Request/requests.cpp \
			../../Helpers/String/string_helpers.cpp \
			../../Helpers/Database/Users/users.cpp \

# Object files
OBJECTS = $(SOURCES:.cpp=.o)

# Executable name
EXECUTABLE = login.cgi

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