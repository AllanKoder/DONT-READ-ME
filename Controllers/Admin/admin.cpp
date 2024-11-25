#include "admin.h"
#include "../../Views/sections/admin/create_user.view.h"
#include "../../Views/redirect.h"
#include "../../Helpers/Request/request.h"
#include "../../Logger/logger.h"
#include "../../Helpers/Session/session.h"
#include "../../Helpers/String/string_helpers.h"
#include "../../Helpers/Database/Users/users.h"
#include <vector>
#include <string>

namespace Controllers
{
    Views::View createUserPage(std::shared_ptr<cgicc::Cgicc> cgi)
    {
        Logger::logInfo("Called createUserPage");
        std::optional<Session::UserInfo> userInfo = Session::userInfo(cgi);
        if (userInfo.has_value() == false)
        {
            // Need to be logged in
            return Views::Redirect(cgi, "/cgi-bin/login.cgi").setNotification(Views::NotificationType::WARNING, "Need to be logged in to view blogs!");
        }
        if (userInfo.value().privilegeLevel != Session::PrivilegeLevel::ADMIN)
        {
            // Need to be admin
            return Views::Redirect(cgi, "/cgi-bin/blogs.cgi").setNotification(Views::NotificationType::WARNING, "You are not admin!");
        }

        return Views::CreateUser(cgi);
    }

    Views::View createUserPost(std::shared_ptr<cgicc::Cgicc> cgi)
    {
        Logger::logInfo("Called createUserPost");
        std::optional<Session::UserInfo> userInfo = Session::userInfo(cgi);
        if (userInfo.has_value() == false)
        {
            // Need to be logged in
            return Views::Redirect(cgi, "/cgi-bin/login.cgi").setNotification(Views::NotificationType::WARNING, "Need to be logged in to view blogs!");
        }
        if (userInfo.value().privilegeLevel != Session::PrivilegeLevel::ADMIN)
        {
            // Need to be admin
            return Views::Redirect(cgi, "/cgi-bin/blogs.cgi").setNotification(Views::NotificationType::WARNING, "You are not admin!");
        }

        // Check CSRF token
        if (!Session::isValidCsrfToken(cgi))
        {
            // Redirect, invalid request
            return Views::Redirect(cgi, "/cgi-bin/blogs.cgi").setNotification(Views::NotificationType::WARNING, "You almost got hacked with a CSRF attack!");
        }

        std::string username = cgi->getElement("username")->getValue();
        std::string email = cgi->getElement("email")->getValue();
        std::string password = cgi->getElement("password")->getValue();

        // Make sure nothing is empty, and have a password policy
        if (username.empty() || email.empty())
        {
            return Views::Redirect(cgi, "/cgi-bin/createUser.cgi").setNotification(Views::NotificationType::WARNING, "Cannot be empty email or username");
        }

        // Ensure Valid Password
        if (!Session::isValidPassword(password))
        {
            return Views::Redirect(cgi, "/cgi-bin/createUser.cgi").setNotification(Views::NotificationType::WARNING, "Is invalid password, must follow policy");
        }

        try
        {
            // Create user
            auto newUser = Database::Requests::CreateUserRequest(
                username,
                email,
                password,
                "user");

            Database::createUser(newUser);

            return Views::Redirect(cgi, "/cgi-bin/blogs.cgi")
                .setNotification(Views::NotificationType::SUCCESS, "Created new User");
        }
        catch (const std::exception &e)
        {
            Logger::logCritical("Error creating user: " + std::string(e.what()));
            return Views::Redirect(cgi, "/cgi-bin/createUser.cgi/")
                .setNotification(Views::NotificationType::WARNING, "Failed to create the user, try again with different fields");
        }
    }
}