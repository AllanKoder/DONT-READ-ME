#include "blog.h"
#include "../../Views/sections/blogs/blogs.view.h"
#include "../../Views/sections/blogs/blog.view.h"
#include "../../Views/sections/blogs/update_blog.view.h"
#include "../../Views/sections/blogs/create_blog.view.h"
#include "../../Views/redirect.h"
#include "../../Helpers/Database/Blogs/blogs.h"
#include "../../Helpers/Database/Blogs/blog_dto.h"
#include "../../Helpers/Request/request.h"
#include "../../Logger/logger.h"
#include "../../Helpers/Session/session.h"
#include "../../Helpers/String/string_helpers.h"
#include <vector>
#include <string>

namespace Controllers
{
    Views::View blogsPage(std::shared_ptr<cgicc::Cgicc> cgi)
    {
        Logger::logInfo("Called blogsPage");
        std::optional<Session::UserInfo> userInfo = Session::userInfo(cgi);
        if (userInfo.has_value() == false)
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

    Views::View blogPage(std::shared_ptr<cgicc::Cgicc> cgi)
    {
        Logger::logInfo("Called blogPage");
        std::optional<Session::UserInfo> userInfo = Session::userInfo(cgi);
        if (userInfo.has_value() == false)
        {
            // Need to be logged in
            return Views::Redirect(cgi, "/cgi-bin/login.cgi")
                .setNotification(Views::NotificationType::WARNING, "Need to be logged in to view blogs!");
        }

        // Get the path blog /blog/{blog_number}
        std::string path = cgi->getEnvironment().getPathInfo();
        std::optional<int> blogNumber = Request::getPathNumber(path);
        if (!blogNumber.has_value())
        {
            return Views::Redirect(cgi, "/cgi-bin/blogs.cgi")
                .setNotification(Views::NotificationType::WARNING, "Invalid blog path parameter integer");
        }

        try
        {
            std::optional<Database::Requests::BlogModel> blog = Database::viewBlog(blogNumber.value());
            if (!blog.has_value())
            {
                Logger::logWarning("Blog not found " + std::to_string(blogNumber.value()));

                return Views::Redirect(cgi, "/cgi-bin/blogs.cgi")
                    .setNotification(Views::NotificationType::WARNING, "Blog not found");
            }

            return Views::Blog(cgi, blog.value());
        }
        catch (sql::SQLException &e)
        {
            Logger::logCritical("Cannot load blog " + std::string(e.what()));
            return Views::Redirect(cgi, "/cgi-bin/blogs.cgi")
                .setNotification(Views::NotificationType::WARNING, "Cannot load the blog specified");
        }
    }

    Views::View upvoteBlog(std::shared_ptr<cgicc::Cgicc> cgi)
    {
        Logger::logInfo("Called upvoteBlog");
        std::optional<Session::UserInfo> userInfo = Session::userInfo(cgi);
        if (!userInfo.has_value())
        {
            // Need to be logged in
            return Views::Redirect(cgi, "/cgi-bin/login.cgi")
                .setNotification(Views::NotificationType::WARNING, "Need to be logged in to upvote blogs!");
        }

        // Check CSRF token
        if (!Session::isValidCsrfToken(cgi))
        {
            Logger::logWarning("Invalid CSRF token for upvoting");
            return Views::Redirect(cgi, "/cgi-bin/blogs.cgi")
                .setNotification(Views::NotificationType::WARNING, "You almost got hacked! someone tried to csrf you!");
        }

        // Get the path blog /blog/{blog_number}
        std::string path = cgi->getEnvironment().getPathInfo();
        std::optional<int> blogNumber = Request::getPathNumber(path);
        if (!blogNumber.has_value())
        {
            return Views::Redirect(cgi, "/cgi-bin/blogs.cgi")
                .setNotification(Views::NotificationType::WARNING, "Could not upvote: Invalid blog path parameter integer");
        }

        try
        {
            Database::upvoteBlog(blogNumber.value());
            Logger::logInfo("Finished upvoting");
        }
        catch (const sql::SQLException &e)
        {
            Logger::logWarning("Failed to upvote blog " + std::string(e.what()));
            return Views::Redirect(cgi, "/cgi-bin/blogs.cgi/")
                .setNotification(Views::NotificationType::WARNING, "Failed to upvote");
        }

        Logger::logInfo("Upvoted the blog, rendering a redirect!");
        return Views::Redirect(cgi, "/cgi-bin/blog.cgi/" + std::to_string(blogNumber.value()))
            .setNotification(Views::NotificationType::SUCCESS, "Upvoted Blog!");
    }

    Views::View downvoteBlog(std::shared_ptr<cgicc::Cgicc> cgi)
    {
        std::optional<Session::UserInfo> userInfo = Session::userInfo(cgi);
        if (userInfo.has_value() == false)
        {
            // Need to be logged in
            return Views::Redirect(cgi, "/cgi-bin/login.cgi")
                .setNotification(Views::NotificationType::WARNING, "Need to be logged in to downvote blogs!");
        }

        // Check CSRF token
        if (!Session::isValidCsrfToken(cgi))
        {
            return Views::Redirect(cgi, "/cgi-bin/blogs.cgi")
                .setNotification(Views::NotificationType::WARNING, "You almost got hacked! someone tried to csrf you!");
        }

        // Get the path blog /blog/{blog_number}
        std::string path = cgi->getEnvironment().getPathInfo();
        std::optional<int> blogNumber = Request::getPathNumber(path);
        if (!blogNumber.has_value())
        {
            return Views::Redirect(cgi, "/cgi-bin/blogs.cgi")
                .setNotification(Views::NotificationType::WARNING, "Could not upvote: Invalid blog path parameter integer");
        }

        try
        {
            Database::downvoteBlog(blogNumber.value());
        }
        catch (const sql::SQLException &e)
        {
            Logger::logWarning("Failed to downvote blog " + std::string(e.what()));
            return Views::Redirect(cgi, "/cgi-bin/blog.cgi/" + blogNumber.value())
                .setNotification(Views::NotificationType::WARNING, "Failed to downvote");
        }

        return Views::Redirect(cgi, "/cgi-bin/blog.cgi/" + std::to_string(blogNumber.value()))
            .setNotification(Views::NotificationType::SUCCESS, "Downvoted Blog!");
    }

    Views::View createBlogPage(std::shared_ptr<cgicc::Cgicc> cgi)
    {
        Logger::logInfo("Called createBlogPage");
        std::optional<Session::UserInfo> userInfo = Session::userInfo(cgi);
        if (userInfo.has_value() == false)
        {
            // Need to be logged in
            return Views::Redirect(cgi, "/cgi-bin/login.cgi").setNotification(Views::NotificationType::WARNING, "Need to be logged in to view blogs!");
        }

        return Views::CreateBlog(cgi);
    }

    Views::View updateBlogPage(std::shared_ptr<cgicc::Cgicc> cgi)
    {
        Logger::logInfo("Called updateBlogPage");

        std::optional<Session::UserInfo> userInfo = Session::userInfo(cgi);
        if (userInfo.has_value() == false)
        {
            // Need to be logged in
            return Views::Redirect(cgi, "/cgi-bin/login.cgi").setNotification(Views::NotificationType::WARNING, "Need to be logged in to view blogs!");
        }

        // Get the path blog /updateBlog.cgi/{blog_number}
        std::string path = cgi->getEnvironment().getPathInfo();
        std::optional<int> blogNumber = Request::getPathNumber(path);
        if (!blogNumber.has_value())
        {
            return Views::Redirect(cgi, "/cgi-bin/blogs.cgi")
                .setNotification(Views::NotificationType::WARNING, "Invalid blog path parameter integer");
        }

        // Get the blog
        std::optional<Database::Requests::BlogModel> blog;
        try
        {
            blog = Database::viewBlog(blogNumber.value());

            if (!blog.has_value())
            {
                Logger::logWarning("Blog not found " + std::to_string(blogNumber.value()));

                return Views::Redirect(cgi, "/cgi-bin/blogs.cgi")
                    .setNotification(Views::NotificationType::WARNING, "Blog not found");
            }
        }
        catch (sql::SQLException &e)
        {
            Logger::logCritical("Cannot load blog " + std::string(e.what()));
            return Views::Redirect(cgi, "/cgi-bin/blogs.cgi")
                .setNotification(Views::NotificationType::WARNING, "Cannot load the blog specified");
        }

        // Need to be the owner of the blog to edit it
        if (userInfo.value().id != blog.value().userId)
        {
            return Views::Redirect(cgi, "/cgi-bin/blogs.cgi")
                .setNotification(Views::NotificationType::WARNING, "You are not the owner of this blog");
        }

        return Views::UpdateBlog(cgi, blog.value());
    }

    Views::View updateBlogPost(std::shared_ptr<cgicc::Cgicc> cgi)
    {
        Logger::logInfo("Called updateBlogPost");

        std::optional<Session::UserInfo> userInfo = Session::userInfo(cgi);
        if (!userInfo.has_value())
        {
            return Views::Redirect(cgi, "/cgi-bin/login.cgi")
                .setNotification(Views::NotificationType::WARNING, "Need to be logged in to update blogs!");
        }

        // Get the path blog /updateBlog.cgi/{blog_number}
        std::string path = cgi->getEnvironment().getPathInfo();
        std::optional<int> blogId = Request::getPathNumber(path);
        if (!blogId.has_value())
        {
            return Views::Redirect(cgi, "/cgi-bin/blogs.cgi")
                .setNotification(Views::NotificationType::WARNING, "Invalid blog path parameter integer");
        }

        // Get form data
        std::string title = cgi->getElement("title")->getValue();
        std::string content = cgi->getElement("content")->getValue();

        try
        {
            // Check if the user is the owner of the blog
            auto blog = Database::viewBlog(blogId.value());
            if (!blog.has_value() || blog.value().userId != userInfo.value().id)
            {
                return Views::Redirect(cgi, "/cgi-bin/blogs.cgi")
                    .setNotification(Views::NotificationType::WARNING, "You are not authorized to edit this blog");
            }

            // Create a BlogUpdatePost object
            Database::Requests::BlogUpdatePost updatePost(title, content, blogId.value());

            // Call the updateBlog function
            Database::updateBlog(updatePost);

            return Views::Redirect(cgi, "/cgi-bin/blog.cgi/" + std::to_string(blogId.value()))
                .setNotification(Views::NotificationType::SUCCESS, "Blog updated successfully");
        }
        catch (const std::exception &e)
        {
            Logger::logCritical("Error updating blog: " + std::string(e.what()));
            return Views::Redirect(cgi, "/cgi-bin/updateBlog.cgi/" + std::to_string(blogId.value()))
                .setNotification(Views::NotificationType::WARNING, "Failed to update blog: " + std::string(e.what()));
        }
    }

    Views::View postBlogPage(std::shared_ptr<cgicc::Cgicc> cgi)
    {
        Logger::logInfo("Called postBlogPage");
        std::optional<Session::UserInfo> userInfo = Session::userInfo(cgi);
        if (userInfo.has_value() == false)
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
        if (postData.count("title") == 0 || postData.count("content") == 0 || postData.count("csrf_token") == 0)
        {
            Logger::logWarning("Invalid parameters for creating blog");
            // Invalid parameters, notify and redirect back to post
            return Views::Redirect(cgi, "/cgi-bin/createBlog.cgi")
                .setNotification(Views::NotificationType::WARNING, "Please fill out all fields.");
        }

        // CSRF Token
        if (!Session::isValidCsrfToken(cgi))
        {
            return Views::Redirect(cgi, "/cgi-bin/createBlog.cgi")
                .setNotification(Views::NotificationType::WARNING, "You almost got hacked! someone tried to csrf you!");
        }

        int dtoUserId = userInfo.value().id;
        std::string dtoContent = StringHelpers::sanitizeString(StringHelpers::urlDecode(postData.at("content")));
        std::string dtoTitle = StringHelpers::sanitizeString(StringHelpers::urlDecode(postData.at("title")));

        Database::Requests::BlogPost blogPost(dtoTitle, dtoContent, dtoUserId);

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