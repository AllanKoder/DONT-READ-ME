# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++17 -Wall -Wextra -Wreorder -g

# Linker flags for libraries
LDFLAGS = -lmariadbcpp -lcgicc -lcrypto++ -lcurl

# Source files
SOURCES = 	emailCode.cpp \
			../../Views/sections/login/login.view.cpp \
			../../Views/sections/login/email.view.cpp \
			../../Views/views.cpp \
			../../Views/components/header.comp.cpp \
			../../Views/components/csrf_token.comp.cpp \
			../../Logger/logger.cpp \
			../../Views/redirect.cpp \
			../../Controllers/Login/login.cpp \
			../../Helpers/Database/db_connection.cpp \
			../../Helpers/Cryptography/crypto.cpp \
			../../Helpers/Email/email.cpp \
			../../Helpers/Session/session.cpp \
			../../Helpers/Request/requests.cpp \
			../../Helpers/String/string_helpers.cpp \
			../../Helpers/Database/Users/users.cpp \

# Object files
OBJECTS = $(SOURCES:.cpp=.o)

# Executable name
EXECUTABLE = emailCode.cgi

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