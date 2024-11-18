#include "string_helpers.h"
#include <string>
#include <sstream>
#include <iomanip>

namespace StringHelpers
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

    std::string urlDecode(const std::string& src) {
        std::string dest;
        size_t i;
        for (i = 0; i < src.length(); i++) {
            if (src[i] == '%') {
                std::istringstream iss(src.substr(i + 1, 2));
                int value;
                if (iss >> std::hex >> value) {
                    dest += static_cast<char>(value);
                    i += 2; // Skip the next two characters
                }
            } else if (src[i] == '+') {
                dest += ' '; // Convert '+' to space
            } else {
                dest += src[i];
            }
        }
        return dest;
    }

    std::string htmlSpecialChars(const std::string& src) {
        std::string result;

        for (char c : src) {
            switch (c) {
                case '&':
                    result += "&amp;"; // Ampersand
                    break;
                case '\"':
                    result += "&quot;"; // Double quote
                    break;
                case '\'':
                    result += "&#039;"; // Single quote
                    break;
                case '<':
                    result += "&lt;"; // Less than
                    break;
                case '>':
                    result += "&gt;"; // Greater than
                    break;
                default:
                    result += c; // Append the character as is
            }
        }
        
        return result;
    }

    // replace strings with lookalikes
    std::string sanitizeString(const std::string& src) {
        std::string result;

        for (char c : src) {
            switch (c) {
                case '&':
                    result += "🙲"; // Ampersand
                    break;
                case '\"':
                    result += "“"; // Double quote 
                    break;
                case '\'':
                    result += "‘"; // Single quote
                    break;
                case '<':
                    result += "＜"; // Less than
                    break;
                case '>':
                    result += "＞;"; // Greater than
                    break;
                default:
                    result += c; // Append the character as is
            }
        }
        
        return result;
    }
}