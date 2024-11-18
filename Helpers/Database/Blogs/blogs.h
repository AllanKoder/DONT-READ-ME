#ifndef DATABASE_BLOGS_H
#define DATABASE_BLOGS_H

#include <memory>
#include <mariadb/conncpp.hpp>
#include "blog_dto.h"
#include <vector>
#include <optional>

namespace Database
{
    std::vector<Requests::BlogModel> viewBlogs(const std::string &query);
    std::optional<Requests::BlogModel> viewBlog(int id);
    void upvoteBlog(int id);
    void downvoteBlog(int id);
    void createBlog(const Requests::BlogPost &post);
    void updateBlog(const Requests::BlogUpdatePost &post);
}

#endif
