#include "Caesar.h"

#include <iostream>

using namespace std;

int main()
{
    Caesar c;
    string text = "Cypher me please OwO";
    string cipheredText = c.Cypher(text);

    cout << "Ciphered text: " << text << endl;

    return 1;
}
