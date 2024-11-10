#ifndef CRYPTO_H
#define CRYPTO_H

#include <string>
#include <array>

namespace Crypto
{
    std::string hash(const std::string& data, const std::string& salt);
    std::array<unsigned char, 32> hmac(const std::string& data);
}
#endif
