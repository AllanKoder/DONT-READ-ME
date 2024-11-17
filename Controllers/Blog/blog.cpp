#include "blog.h"
#include "../../Views/sections/blogs/blogs.view.h"
#include "../../Helpers/Database/Blogs/blogs.h"
#include "../../Helpers/Request/request.h"
#include <vector>

namespace Controllers
{
    Views::View blogsPage(std::shared_ptr<cgicc::Cgicc> cgi)
    {
        try {
            std::string queryStrings = cgi->getEnvironment().getQueryString();
            std::string searchString = Request::getQueryValue("search", queryStrings);

            std::vector<Database::Requests::BlogPost> blogs = Database::viewBlogs(searchString);
            return Views::Blogs(cgi, blogs);
        }
        catch (sql::SQLException e){
            return Views::Blogs(cgi, {}).setNotification(Views::NotificationType::WARNING, "Cannot load blogs :(");
        }
    }
}