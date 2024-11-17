#include "request.h"
#include "vector"
#include "../String/string_helpers.h"

namespace Request
{
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