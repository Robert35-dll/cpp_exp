#pragma once
#ifndef string
#include <string>
#endif

using namespace std;

class Caesar
{
    private:
        int StandardKey;

    public:
        Caesar(int cipherKey_ = 2)
            : StandardKey(cipherKey_)
        {};
        ~Caesar() {};

        string Cipher(string decipheredText);
        string Cipher(string decipheredText, int cipherKey);
        string Decipher(string cipheredText);
        string Decipher(string cipheredText, int cipherKey);

        bool IsDecipherable(string decipheredText, string cipheredText);
        int GetCipherKey(string decipheredText, string cipheredText);
};