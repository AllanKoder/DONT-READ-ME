#ifndef VIEWS_H
#define VIEWS_H

#include <string>

namespace Views
{
    class View
    {
    private:
        std::string title;
        std::string headers;
        std::string body;
    public:
        void render();
        View& setHeader(std::string header);
        View& setCookie(std::string cookie);
        View& setTitle(std::string newTitle);
        View& setBody(std::string body);
    };   
}
#endif