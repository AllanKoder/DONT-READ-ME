#ifndef BLOG_REQUEST_H
#define BLOG_REQUEST_H

#include "../../../config.h"
#include <string>

namespace Database::Requests
{
    struct BlogPost {
        std::string name;
        std::string dateCreated;
        std::string title;
    };
}

#endif