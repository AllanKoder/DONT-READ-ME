#ifndef BLOG_REQUEST_H
#define BLOG_REQUEST_H

#include "../../../config.h"
#include <string>
#include <utility>

namespace Database::Requests
{
    class BlogModel
    {
    public:
        BlogModel(
            std::string username,
            std::string content,
            int upvotes,
            std::string dateCreated,
            std::string title) : username(std::move(username)),
                                 content(std::move(content)),
                                 upvotes(upvotes),
                                 dateCreated(std::move(dateCreated)),
                                 title(std::move(title)) {}

        // Member variables
        std::string username;
        std::string content;
        int upvotes;
        std::string dateCreated;
        std::string title;
    };

    class BlogPost
    {
    public:
        BlogPost(
            std::string title,
            std::string content,
            int userId) : title(std::move(title)),
                          content(std::move(content)),
                          userId(userId) {}

        std::string title;
        std::string content;
        int userId;
    };

}

#endif