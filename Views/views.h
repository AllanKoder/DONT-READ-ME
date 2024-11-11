#ifndef VIEWS_H
#define VIEWS_H

#include <vector>
#include <string>
#include <cgicc/HTTPCookie.h>
#include <cgicc/HTTPHTMLHeader.h>

namespace Views
{
    class View
    {
    private:
        std::string title;
        std::string headers;
        std::string body;
        std::vector<cgicc::HTTPCookie> cookies;
        cgicc::HTTPHTMLHeader getHeader();
        View();
         
    public:
        void render();
        View& setHeader(std::string header);
        View& setCookie(cgicc::HTTPCookie cookie);
        View& setTitle(std::string newTitle);
        View& setBody(std::string body);
    };   
}
#endif