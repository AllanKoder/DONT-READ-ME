#ifndef STRING_HELPERS_H
#define STRING_HELPERS_H
#include <string>
#include <vector>

namespace StringHelpers
{
    std::vector<std::string> split(std::string s, std::string delimiter);
    std::string urlDecode(const std::string& src);
    std::string htmlSpecialChars(const std::string& src);
}

#endif