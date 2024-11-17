#include "blogs.h"
#include <memory>
#include <mariadb/conncpp.hpp>
#include "../db_connection.h"

namespace Database
{
    std::vector<Requests::BlogPost> viewBlogs(const std::string& query)
    {
        std::vector<Requests::BlogPost> posts = {
            {"John Doe", "2024-01-15", "First Blog Post"},
            {"Jane Smith", "2024-02-20", "Another Interesting Post"},
            {"Alice Johnson", "2024-03-05", "Learning C++ with CGICC"},
            {"Bob Brown", "2024-04-10", "Tailwind CSS Tips"}
        };

        return posts;
    }
}