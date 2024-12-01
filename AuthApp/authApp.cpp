#include <iostream>
#include "../env.h"
#include "../Helpers/Cryptography/crypto.h"

int main()
{
    std::cout << "App Code is: " << Crypto::getAppCode() << "\n";
}