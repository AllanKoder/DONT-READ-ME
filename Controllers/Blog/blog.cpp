#include "blog.h"
#include "../../Views/sections/blogs/blogs.view.h"
#include "../../Helpers/Database/Blogs/blogs.h"
#include <vector>

namespace Controllers
{
    Views::View blogsPage(std::shared_ptr<cgicc::Cgicc> cgi)
    {
        std::vector<Database::Requests::BlogPost> blogs = Database::viewBlogs("");

        return Views::Blogs(cgi, blogs);
    }
}