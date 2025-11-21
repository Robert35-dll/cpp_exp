#include "SIMcard.h"

/**
 * @brief Adds a new contact to the SIMcard.
 * @note If provided PIN is incorrect, no contact will be added.
 * @param name_: The name of a new contact.
 * @param nummer_: The number of a new contact.
 * @param pin_: The PIN number of the SIMcard.
 * @retval True, if a contact was added successfully. False otherwise.
 */
bool SIMcard::trageEin(string name_, int nummer_, unsigned int pin_)
{
    if (pin_ != PIN || nummer_ == 0)
    {
        return false;
    }

    Eintrag neuerEintrag;
    neuerEintrag.name = name_;
    neuerEintrag.nummer = nummer_;

    Telefonbuch.push_back(neuerEintrag);

    return true;
}

/**
 * @brief Searches for the number of a contact with given name.
 * @note If provided PIN is incorrect, no search will be performed.
 * @param name_: The name of a contact to search for.
 * @param pin_: The PIN number of the SIMcard.
 * @retval A found contact number as `int` or `0`, if contact isn't
 *         on the list, or `-1`, if the given PIN number isn't correct.
 */
int SIMcard::sucheNummer(string name_, unsigned int pin_)
{
    if (pin_ != PIN)
    {
        return -1;
    }

    Eintrag e;
    for (size_t i = 0; i < Telefonbuch.size(); i++)
    {
        e = Telefonbuch.at(i);
        if (e.name == name_)
        {
            return e.nummer;
        }
    }

    return 0;
}