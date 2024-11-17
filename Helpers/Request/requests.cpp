#include "request.h"
#include "vector"
#include "../String/string_helpers.h"

namespace Request
{
    std::string getQueryValue(const std::string& key, const std::string& queryString)
    {
        // Find the position of the key in the query string
        size_t pos = queryString.find(key + "=");
        if (pos != std::string::npos)
        {
            size_t start = pos + key.length() + 1; // Move past the key and '='
            size_t end = queryString.find_first_of("&", start); // Find '&' or end of string
            if (end == std::string::npos)
            {
                end = queryString.length(); // No '&' found, take till the end
            }

            // Extract and return the value
            return queryString.substr(start, end - start);
        }

        // Return an empty string if the key is not found
        return "";
    }

    std::unordered_map<std::string, std::string> getPostDataToMap(std::string data)
    {
        // Data is in the format of: test=fdsfsd&key2=value3
        std::unordered_map<std::string, std::string> output;
        std::vector<std::string> keyValuePairs = StringHelpers::split(data, "&");
        for(std::string keyValuePair : keyValuePairs)
        {
            std::vector<std::string> keyValue = StringHelpers::split(keyValuePair, "=");
            output.insert_or_assign(keyValue[0], keyValue[1]);
        }

        return output;
    }
}