# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++17 -Wall -Wextra -Wreorder -g

# Linker flags for libraries
LDFLAGS = -lmariadbcpp -lcgicc -lcrypto++

# Source files
SOURCES =  downvoteBlog.cpp \
            ../../Views/views.cpp \
            ../../Views/components/header.comp.cpp \
			../../Views/components/csrf_token.comp.cpp \
            ../../Views/sections/blogs/blog.view.cpp \
            ../../Views/sections/blogs/blogs.view.cpp \
            ../../Views/sections/blogs/create_blog.view.cpp \
            ../../Controllers/Blog/blog.cpp \
            ../../Logger/logger.cpp \
            ../../Views/redirect.cpp \
            ../../Helpers/Cryptography/crypto.cpp \
            ../../Helpers/Session/session.cpp \
            ../../Helpers/Request/requests.cpp \
            ../../Helpers/String/string_helpers.cpp \
            ../../Helpers/Database/db_connection.cpp \
            ../../Helpers/Database/Users/users.cpp \
            ../../Helpers/Database/Blogs/blogs.cpp  \

# Object files (replace .cpp with .o)
OBJECTS = $(SOURCES:.cpp=.o)


# Object files
OBJECTS = $(SOURCES:.cpp=.o)

# Executable name
EXECUTABLE = downvoteBlog.cgi

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