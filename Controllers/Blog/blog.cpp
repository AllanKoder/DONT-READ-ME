#include "blog.h"
#include "../../Views/sections/blogs/blogs.view.h"
#include "../../Views/sections/blogs/create_blog.view.h"
#include "../../Views/redirect.h"
#include "../../Helpers/Database/Blogs/blogs.h"
#include "../../Helpers/Request/request.h"
#include "../../Logger/logger.h"
#include "../../Helpers/Session/session.h"
#include <vector>

namespace Controllers
{
    Views::View blogsPage(std::shared_ptr<cgicc::Cgicc> cgi)
    {
        std::optional<int> userId = Session::userId(cgi);
        if (userId.has_value() == false)
        {
            // Need to be logged in
            return Views::Redirect(cgi, "/cgi-bin/login.cgi").setNotification(Views::NotificationType::WARNING, "Need to be logged in to view blogs!");
        }
        try {
            std::string queryStrings = cgi->getEnvironment().getQueryString();
            std::string searchString = Request::getQueryValue("search", queryStrings);

            std::vector<Database::Requests::BlogPost> blogs = Database::viewBlogs(searchString);
            return Views::Blogs(cgi, blogs);
        }
        catch (sql::SQLException &e){
            Logger::logCritical("Cannot load blogs " + std::string(e.what()));
            return Views::Blogs(cgi, {}).setNotification(Views::NotificationType::WARNING, "Cannot load blogs :(");
        }
    }

    Views::View createBlogPage(std::shared_ptr<cgicc::Cgicc> cgi)
    {
        std::optional<int> userId = Session::userId(cgi);
        if (userId.has_value() == false)
        {
            // Need to be logged in
            return Views::Redirect(cgi, "/cgi-bin/login.cgi").setNotification(Views::NotificationType::WARNING, "Need to be logged in to view blogs!");
        }

        return Views::CreateBlog(cgi);
    }
}