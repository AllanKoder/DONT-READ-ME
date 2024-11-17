#ifndef REQUEST_HELPERS_H
#define REQUEST_HELPERS_H

#include <unordered_map>
#include <string>
#include <optional>

namespace Request
{
    std::string getQueryValue(const std::string& key, const std::string& queryString);
    std::unordered_map<std::string, std::string> getPostDataToMap(std::string data);
    std::optional<int> getPathNumber(const std::string &path);
}

#endif