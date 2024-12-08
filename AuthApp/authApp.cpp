#include <iostream>
#include "../env.h"
#include "../Helpers/Cryptography/crypto.h"

// The application which shows the code for admin login
int main()
{
    std::string challengeCode;

    std::cout << "Input the challenge code:";
    std::cin >> challengeCode;
    std::cout << "App Code is: " << Crypto::getAppCode(challengeCode) << "\n";
}