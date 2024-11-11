#include "request.h"
#include "vector"

namespace Request
{
    std::vector<std::string> split(std::string s, std::string delimiter)
    {
        if (s.length() == 0)
        {
            return {};
        }

        size_t pos_start = 0, pos_end, delim_len = delimiter.length();
        std::string token;
        std::vector<std::string> res;

        while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos)
        {
            token = s.substr(pos_start, pos_end - pos_start);
            pos_start = pos_end + delim_len;
            res.push_back(token);
        }

        res.push_back(s.substr(pos_start));
        return res;
    }

    std::unordered_map<std::string, std::string> getPostDataToMap(std::string data)
    {
        // Data is in the format of: test=fdsfsd&key2=value3
        std::unordered_map<std::string, std::string> output;
        std::vector<std::string> keyValuePairs = split(data, "&");
        for(std::string keyValuePair : keyValuePairs)
        {
            std::vector<std::string> keyValue = split(keyValuePair, "=");
            output.insert_or_assign(keyValue[0], keyValue[1]);
        }

        return output;
    }
}