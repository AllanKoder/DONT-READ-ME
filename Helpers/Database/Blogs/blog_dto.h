#ifndef BLOG_REQUEST_H
#define BLOG_REQUEST_H

#include "../../../config.h"
#include <string>

namespace Database::Requests
{
    struct BlogModel
    {
        std::string username;
        std::string content;
        int upvotes;
        std::string dateCreated;
        std::string title;
    };

    struct BlogPost
    {
        std::string title;
        std::string content;
        int userId;
    };
}

#endif