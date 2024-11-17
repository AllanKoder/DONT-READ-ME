#ifndef USERS_H
#define USERS_H

#include <memory>
#include <mariadb/conncpp.hpp>
#include "blog_post.h"
#include <vector>

namespace Database
{
    std::vector<Requests::BlogPost> viewBlogs(const std::string& query);
}

#endif
