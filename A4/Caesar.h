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
        Caesar(int cypherKey_ = 2)
            : StandardKey(cypherKey_)
        {};
        ~Caesar() {};

        string Cypher(string decipheredText);
        string Cypher(string decipheredText, int cypherKey /*= 2*/);
        string Decipher(string cipheredText);
        string Decipher(string cipheredText, int cypherKey /*= 2*/);

        bool IsDecipherable(string decipheredText, string cipheredText);
        int GetCypherKey(string decipheredText, string cipheredText);
};