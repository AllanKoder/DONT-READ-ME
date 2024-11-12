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
        WARNING,
        SUCCESS,
    };

    class View
    {
    private:
        std::string redirectUrl;
        std::string body;
        std::string headers;
        std::string scripts;
        std::string title;
        std::vector<std::string> cookies;
        std::string getHeader();
        std::shared_ptr<cgicc::Cgicc> cgi;
    public:
        View(std::shared_ptr<cgicc::Cgicc> cgi);
        void render();
        View& setHeader(std::string header);
        View& setRedirect(const std::string& url);
        View& setCookie(std::string cookie);
        View& setNotification(NotificationType notification, std::string message);
        View& setTitle(std::string newTitle);
        View& setBody(std::string body);
    };   
}

#endif