#include "Caesar.h"

int main() {
    return 1;
}

string Caesar::Cypher(string decipheredText)
{
    string cipheredText;

    for (char c : decipheredText)
    {
        cipheredText += c + StandardKey;
    }

    return cipheredText;
}

string Caesar::Cypher(string decipheredText, int cypherKey = 2)
{
    string cipheredText;

    for (char c : decipheredText)
    {
        cipheredText += c + cypherKey;
    }

    return cipheredText;
}

string Caesar::Decipher(string cipheredText, int cypherKey)
{
    return "";
}

bool Caesar::IsDecipherable(string decipheredText, string cipheredText)
{
    return false;
}

int Caesar::GetCypherKey(string decipheredText, string cipheredText)
{
    return 0;
}