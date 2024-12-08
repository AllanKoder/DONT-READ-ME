#ifndef STRING_HELPERS_H
#define STRING_HELPERS_H

#include <string>
#include <vector>

/**
 * @brief A series of basic helper functions for the handling of strings.
 * 
 * Functions to help with string processing. 
 */
namespace StringHelpers
{
    /**
     * @brief Splits a string into a vector of substrings based on a delimiter.
     * 
     * @param s The input string to be split.
     * @param delimiter The delimiter string used to split the input string.
     * @return std::vector<std::string> A vector containing the split substrings.
     */
    std::vector<std::string> split(std::string s, std::string delimiter);
    
    /**
     * @brief Decodes a URL-encoded string.
     * 
     * This function converts percent-encoded characters back to their original representation.
     * 
     * @param src The URL-encoded input string.
     * @return std::string The decoded output string.
     */
    std::string urlDecode(const std::string& src);
    
    /**
     * @brief Converts special characters in a string to their HTML entities.
     * 
     * This function replaces characters such as "&", "<", ">", "\"", and "'" with their corresponding HTML entities.
     * 
     * @param src The input string containing special characters.
     * @return std::string The output string with HTML entities.
     */
    std::string htmlSpecialChars(const std::string& src);

    /**
     * @brief Sanitizes a string by replacing certain characters with lookalikes.
     * 
     * This function replaces characters with visually similar alternatives to prevent XSS injections.
     * 
     * @param src The input string to be sanitized.
     * @return std::string The sanitized output string.
     */
    std::string sanitizeString(const std::string& src);
}

#endif