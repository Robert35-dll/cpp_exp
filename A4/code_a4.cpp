#include "./A4.1/Caesar.h"

#include <iostream>

using namespace std;

// A4.1 Functions
void TestCaesarCiphering();

int main()
{
    // A4.1
    TestCaesarCiphering();

    return 1;
}

#pragma region [A4.1]

/**
 * @brief Runs all functions of Caesar class with hard coded input.
 */
void TestCaesarCiphering()
{
    Caesar caesar;
    string text = "Cipher me please OwO";
    string cipher = caesar.Cipher(text, -5);

    cout << "[>] Original text: " << text << endl;
    cout << " |-<*> Ciphered text: " << cipher << endl;

    cout << " |-<*> Deciphered text: ";
    cout << caesar.Decipher(cipher, -5) << endl;

    cout << " |-<?> Is standard cipher key used: ";
    cout << caesar.IsDecipherable(text, cipher) << endl;

    cout << " |-<*> Cipher key used: ";
    cout << caesar.GetCipherKey(text, cipher) << endl;
}

#pragma endregion [A4.1]