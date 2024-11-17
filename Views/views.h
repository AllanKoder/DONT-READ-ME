#ifndef VIEWS_H
#define VIEWS_H

#include <vector>
#include <string>
#include <memory>
#include <cgicc/HTTPCookie.h>
#include <cgicc/HTTPHTMLHeader.h>
#include <cgicc/Cgicc.h>

namespace Views
{
    enum class NotificationType
    {
        NONE,
        WARNING,
        SUCCESS,
    };

    class View
    {
    private:
        std::string redirectUrl;
        std::string body;
        std::string headers;
        std::string title;
        std::vector<std::string> cookies;
        std::string getHeader();
        std::shared_ptr<cgicc::Cgicc> cgi;

        void getNotifications();
    public:
        View(std::shared_ptr<cgicc::Cgicc> cgi);
        void render();
        View& setHeader(std::string header);
        View& setRedirect(const std::string& url);
        View& setCookie(std::string cookie);
        View& setTitle(std::string newTitle);
        View& setBody(std::string body);
        View& setNotification(NotificationType type, const std::string& message);
    };   
}

#endif