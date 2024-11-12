#include "views.h"
#include <iostream>
#include <cgicc/HTMLClasses.h>
#include <cgicc/HTTPRedirectHeader.h>
#include "../Logger/logger.h"
#include <sstream>
#include "components/header.comp.h"

namespace Views
{
    View::View(std::shared_ptr<cgicc::Cgicc> _cgi) : redirectUrl(""), body(""), headers(""), cgi(_cgi)
    {
        title = "No Title";
        cookies.clear();

        // Libraries
        scripts = "<script src=\"https://cdn.tailwindcss.com\"></script>\n";
    }

    std::string View::getHeader()
    {
        std::ostringstream outputHeader;

        if (!redirectUrl.empty())
        {
            // There is a redirect, set it as the header
            outputHeader << "Status: 301 Moved Permanently\n";
            outputHeader << "Location: " << redirectUrl << "\n";
        }
        else
        {
            // If there's no redirect, proceed with the normal header
            outputHeader << "Content-Type: text/html\n";
        }

        // Add custom headers
        outputHeader << headers;

        // Add cookies
        for (const auto& cookie : cookies)
        {
            outputHeader << "Set-Cookie: " << cookie << "\n";
        }

        outputHeader << "\n";
        return outputHeader.str();
    }

    void View::render()
    {
        // Output HTTP headers
        std::cout << getHeader() << "\n";
        
        // Start HTML document
        std::cout << "<html lang=\"en\" class=\"h-full\">\n";
    
        // Start the <head>
        std::cout << "<head>\n";
        std::cout << "<meta charset=\"UTF-8\">\n";
        std::cout << "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n";
        std::cout << "<title>" << title << "</title>\n";
        std::cout << "<script src=\"https://cdn.tailwindcss.com\"></script>\n";
        std::cout << scripts << "\n";
        std::cout << "</head>\n";
        
        // Start the body
        std::cout << "<body class=\"h-full bg-white\">\n";
        
        std::cout << Views::Header(cgi);
        
        // Main content
        std::cout << "<main>\n";
        std::cout << "  <div class=\"max-w-7xl mx-auto py-6 sm:px-6 lg:px-8\">\n";
        std::cout << "    <div class=\"px-4 py-6 sm:px-0\">\n";
        std::cout << "      <div class=\"border-0 rounded-lg h-96\">\n";
        std::cout << body << "\n";
        std::cout << "      </div>\n";
        std::cout << "    </div>\n";
        std::cout << "  </div>\n";
        std::cout << "</main>\n";
        
        // End HTML document
        std::cout << "</body>\n";
        std::cout << "</html>\n";
    }

    View& View::setRedirect(const std::string& url) {
        redirectUrl = url;
        return *this;
    }
    
    View& View::setHeader(std::string header)
    {
        headers += header + "\r\n";
        return *this;
    }

    View& View::setCookie(std::string cookie)
    {
        cookies.push_back(cookie);
        return *this;
    }

    View& View::setBody(std::string newBody)
    {
        body = newBody;
        return *this;
    }

    View& View::setTitle(std::string newTitle)
    {
        title = newTitle;
        return *this;
    }
    
    View& View::setNotification(NotificationType type, std::string message)
    {

        return *this;
    }
}