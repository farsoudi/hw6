#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <algorithm>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

using namespace std;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        //stores up to 6 'w' (a1, a2, a3, a4, a5, a6) values
        unsigned long long w[5] = {0};
        const std::string kk (k.rbegin(), k.rend());
        for (size_t i = 0; i < 5; ++i) {
            if (i*6 < kk.size()) { //For shorter strings
                string sub(kk.substr(i*6, 6));
                string subr(sub.rbegin(), sub.rend());
                for (char c : subr) {
                    w[4-i] = w[4-i] * 36 + letterDigitToNumber(c);
                }
            }
        }
        HASH_INDEX_T hk = 0;
        for (size_t i = 0 ; i < 5 ; ++i) {
            hk += w[i] * rValues[i];
        }
        return hk;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        if (letter >= '0' && letter <= '9') {
            return (letter-'0' + 26);
        } else {
            char lower = tolower(letter);
            if (lower >= 'a' && lower <= 'z'){
                return lower-'a';
            }
        }
        return letter;
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
