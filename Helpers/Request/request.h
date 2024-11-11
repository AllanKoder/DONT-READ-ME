#ifndef REQUEST_HELPERS_H
#define REQUEST_HELPERS_H

#include <unordered_map>
#include <string>

namespace Request
{
    std::unordered_map<std::string, std::string> getPostDataToMap(std::string data);
}

#endif