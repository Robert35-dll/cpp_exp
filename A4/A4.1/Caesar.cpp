#include "Caesar.h"

/**
 * @brief Encrypts the given text according to
 *        Caesar's cipher algorithm.
 * @note The standard cipher key passed at instantiation is used.
 * @param decipheredText: The text to cipher.
 * @retval The encrypted text as a `string`.
 */
string Caesar::Cipher(string decipheredText)
{
    return Caesar::Cipher(decipheredText, StandardKey);
}

/**
 * @brief Encrypts the given text according to
 *        Caesar's cipher algorithm.
 * @param decipheredText: The text to cipher.
 * @param cipherKey: The amount of chars (in ASCII/UTF order)
 *                   to shift the encrypted text for.
 * @retval The encrypted text as a `string`.
 */
string Caesar::Cipher(string decipheredText, int cipherKey)
{
    string cipheredText;

    for (char c : decipheredText)
    {
        cipheredText += c + cipherKey;
    }

    return cipheredText;
}

/**
 * @brief Dencrypts the given text according to
 *        Caesar's cipher algorithm.
 * @note The standard cipher key passed at instantiation is used.
 * @param cipheredText: The text to decipher.
 * @retval The decrypted text as a `string`.
 */
string Caesar::Decipher(string cipheredText)
{
    return Caesar::Decipher(cipheredText, StandardKey);
}

/**
 * @brief Decrypts the given text according to
 *        Caesar's cipher algorithm.
 * @param cipheredText: The text to decipher.
 * @param cipherKey: The amount of chars (in ASCII/UTF order)
 *                   to shift the decrypted text for.
 * @retval The decrypted text as a `string`.
 */
string Caesar::Decipher(string cipheredText, int cipherKey)
{
    string decipheredText;

    for (char c : cipheredText)
    {
        decipheredText += c - cipherKey;
    }

    return decipheredText;
}

/**
 * @brief Checks, whether the given original text was encrypted with the
 *        standard cipher key passed at instantiation or not.
 * @note If any character of an encryption was modified, this encryption
 *       is considered undecipherable.
 * @param decipheredText: The original text.
 * @param cipheredText: An encryption of the original text.
 * @retval True, if the original text was correctly encrypted
 *         using Caesar's cipher algorithm, otherwise false.
 */
bool Caesar::IsDecipherable(string decipheredText, string cipheredText)
{
    for (size_t i = 0; i < decipheredText.length(); i++)
    {
        if (decipheredText[i] + StandardKey != cipheredText[i])
        {
            return false;
        }
    }

    return true;
}

/**
 * @brief Searches for an encryption key in range of 1000 + 1
 *        used by Caesar's cipher algorithm applied to the given texts.
 * @note If any of the texts is an empty string, 0 is returned.
 * @param decipheredText: The original text.
 * @param cipheredText: An encryption of the original text.
 * @retval The amount of chars (in ASCII/UTF order) used
 *         to encrypt the original text as `int` or `0`,
 *         if the key is out of searching range.
 */
int Caesar::GetCipherKey(string decipheredText, string cipheredText)
{
    if (decipheredText.length() == 0 || cipheredText.length() == 0)
    {
        return 0;
    }

    for (int cipherKey = 0; cipherKey <= 1000; cipherKey++)
    {
        if (decipheredText[0] + cipherKey == cipheredText[0])
        {
            return cipherKey;
        }
        if (decipheredText[0] - cipherKey == cipheredText[0])
        {
            return -cipherKey;
        }
    }

    return 0;
}