#ifndef CRYPTO_H
#define CRYPTO_H

#include <string>
#include <array>

namespace Crypto
{
    std::string hash(const std::string& data, const std::string& salt);
    std::string hmac(const std::string& data);
}
#endif
