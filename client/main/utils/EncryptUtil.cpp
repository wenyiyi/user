//
//  Encrypt.cpp
//  user
//
//  Created by Vincent on 2020/6/26.
//  Copyright © 2020 Vincent. All rights reserved.
//

#include "Encrypt.hpp"
#include <algorithm>
#include <iomanip>
#include <sstream>
#include <string>
#include "md5.hpp"

std::string Encrypt::randomSalt()
{
    auto randchar = []() -> char
    {
        const char charset[] =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";
        const size_t max_index = (sizeof(charset) - 1);
        return charset[rand() % max_index];
    };
    std::string str(8, 0);
    std::generate_n(str.begin(), length, randchar);
    return str;
}

std::string Encrypt::getTokenForUser(std::string mobile)
{ auto randchar = []() -> char
       {
           const char charset[] =
               "0123456789"
               "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
               "abcdefghijklmnopqrstuvwxyz";
           const size_t max_index = (sizeof(charset) - 1);
           return charset[rand() % max_index];
       };
       std::string str(32, 0);
       std::generate_n(str.begin(), 32, randchar);
       return str;
    return random_string(32);
}

std::string Encrypt::md5(const std::string input)
{
    return MD5(input).toStr();
}

