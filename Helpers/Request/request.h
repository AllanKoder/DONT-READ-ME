#ifndef REQUEST_HELPERS_H
#define REQUEST_HELPERS_H

#include <unordered_map>
#include <string>
#include <optional>

namespace Request
{
    /**
     * @brief Retrieves the value associated with a specific key from a query string.
     * 
     * This function parses the query string and returns the value corresponding to the provided key.
     * If the key is not found, an empty string is returned.
     * 
     * @param key The key for which to retrieve the value.
     * @param queryString The full query string to search within.
     * @return std::string The value associated with the key, or an empty string if not found.
     */
    std::string getQueryValue(const std::string& key, const std::string& queryString);

    /**
     * @brief Extracts a number from a given path string.
     * 
     * This function attempts to find and return an integer from the specified path. 
     * If no valid number is found, an empty optional is returned.
     * 
     * @param path The path string from which to extract the number.
     * @return std::optional<int> An optional containing the extracted number if found, otherwise nullopt.
     */
    std::optional<int> getPathNumber(const std::string &path);
}

#endif