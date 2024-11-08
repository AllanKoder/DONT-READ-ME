#include <iostream>
#include <string>
#include <crypto++/cryptlib.h>
#include <crypto++/sha.h>
#include <crypto++/hex.h>

std::string hash(const std::string& data, const std::string& salt) {
    // Combine data and salt
    std::string combined = data + salt;

    // Prepare for hashing
    CryptoPP::byte abDigest[CryptoPP::SHA256::DIGESTSIZE];
    CryptoPP::SHA256 hash;

    // Calculate the digest
    hash.CalculateDigest(abDigest, reinterpret_cast<const CryptoPP::byte*>(combined.data()), combined.size());

    // Encode the digest to a hex string
    std::string hexDigest;
    CryptoPP::HexEncoder encoder(new CryptoPP::StringSink(hexDigest));
    encoder.Put(abDigest, sizeof(abDigest));
    encoder.MessageEnd();

    return hexDigest; // Return the hexadecimal representation of the digest
}
