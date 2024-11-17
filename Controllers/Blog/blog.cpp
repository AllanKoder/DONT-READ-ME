#include "blog.h"
#include "../../Views/sections/blogs/blogs.view.h"
#include "../../Views/sections/blogs/create_blog.view.h"
#include "../../Views/redirect.h"
#include "../../Helpers/Database/Blogs/blogs.h"
#include "../../Helpers/Database/Blogs/blog_dto.h"
#include "../../Helpers/Request/request.h"
#include "../../Logger/logger.h"
#include "../../Helpers/Session/session.h"
#include "../../Helpers/String/string_helpers.h"
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
        try
        {
            std::string queryStrings = cgi->getEnvironment().getQueryString();
            std::string searchString = Request::getQueryValue("search", queryStrings);

            std::vector<Database::Requests::BlogModel> blogs = Database::viewBlogs(searchString);
            return Views::Blogs(cgi, blogs);
        }
        catch (sql::SQLException &e)
        {
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

    Views::View postBlogPage(std::shared_ptr<cgicc::Cgicc> cgi)
    {
        std::optional<int> userId = Session::userId(cgi);
        if (userId.has_value() == false)
        {
            // Need to be logged in
            return Views::Redirect(cgi, "/cgi-bin/login.cgi").setNotification(Views::NotificationType::WARNING, "Need to be logged in to view blogs!");
        }

        // Check the forms, if the values are correct

        cgicc::CgiEnvironment env = cgi->getEnvironment();
        std::string requestBody = env.getPostData();

        Logger::logInfo("Got Request body. It is the following: " + requestBody);
        std::unordered_map<std::string, std::string> postData = Request::getPostDataToMap(requestBody);

        // Check if the user has filled the parameters for posting
        if (postData.count("title") == 0 || postData.count("content") == 0)
        {
            Logger::logWarning("Invalid parameters for creating blog");
            // Invalid parameters, notify and redirect back to post
            return Views::Redirect(cgi, "/cgi-bin/createBlog.cgi")
                .setNotification(Views::NotificationType::WARNING, "Please fill out all fields.");
        }

        Database::Requests::BlogPost blogPost;

        blogPost.userId = userId.value();
        blogPost.content = StringHelpers::htmlSpecialChars(StringHelpers::urlDecode(postData.at("content")));
        blogPost.title = StringHelpers::htmlSpecialChars(StringHelpers::urlDecode(postData.at("title")));

        // Create the blog under the user
        try
        {
            Database::createBlog(blogPost);
            Logger::logInfo("Have created a blog");
        }
        catch (const sql::SQLException &e)
        {
            Logger::logCritical("Cannot post blog post " + std::string(e.what()));
            return Views::Redirect(cgi, "/cgi-bin/createBlog.cgi")
                .setNotification(Views::NotificationType::WARNING, "Failed to save blog");
        }

        // Have created the blog
        return Views::Redirect(cgi, "/cgi-bin/blogs.cgi")
            .setNotification(Views::NotificationType::SUCCESS, "Success!");
    }
}