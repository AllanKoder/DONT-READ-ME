#ifndef HASH_H
#define HASH_H

#include <string>
namespace Hash
{
    std::string hash(const std::string& data, const std::string& salt);
}
#endif