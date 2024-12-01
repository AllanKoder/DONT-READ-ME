# common.mk

# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++17 -Wall -Wextra -Wreorder -g

# Linker flags for libraries
LDFLAGS = -lmariadbcpp -lcgicc -lcrypto++ -lcurl

# Common source files
COMMON_SOURCES = \
    ../../Views/views.cpp \
	../../Views/redirect.cpp \
    ../../Views/components/header.comp.cpp \
    ../../Views/components/csrf_token.comp.cpp \
	../../Views/sections/login/login.view.cpp \
	../../Views/sections/login/email.view.cpp \
    ../../Views/sections/blogs/blogs.view.cpp \
    ../../Views/sections/blogs/update_blog.view.cpp \
    ../../Views/sections/blogs/blog.view.cpp \
    ../../Views/sections/blogs/create_blog.view.cpp \
	../../Views/sections/admin/create_user.view.cpp \
	../../Views/sections/seed/seed.view.cpp \
	../../Controllers/Admin/admin.cpp \
	../../Controllers/Login/login.cpp \
    ../../Controllers/Blog/blog.cpp \
	../../Controllers/Seeding/seed.cpp \
    ../../Logger/logger.cpp \
    ../../Helpers/Cryptography/crypto.cpp \
    ../../Helpers/Email/email.cpp \
    ../../Helpers/Session/session.cpp \
    ../../Helpers/Request/requests.cpp \
    ../../Helpers/String/string_helpers.cpp \
    ../../Helpers/Database/db_connection.cpp \
    ../../Helpers/Database/Users/users.cpp \
    ../../Helpers/Database/Blogs/blogs.cpp

# Common rules
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
