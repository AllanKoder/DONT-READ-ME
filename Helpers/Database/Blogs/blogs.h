#ifndef DATABASE_BLOGS_H
#define DATABASE_BLOGS_H

#include <memory>
#include <mariadb/conncpp.hpp>
#include "blog_dto.h"
#include <vector>

namespace Database
{
    std::vector<Requests::BlogModel> viewBlogs(const std::string& query);
    void createBlog(const Requests::BlogPost& post);
}

#endif
