#include <iostream>
#include <string>
#include <map>

#include "../A4/A4.3/SimpleCLI.h"

using namespace std;

// A7.1 Functions
void RunContactBook(SimpleCLI* const);

int main()
{
    SimpleCLI* const cli = new SimpleCLI();

    // A7.1
    cout << "[*] A7.1\n |" << endl;
    RunContactBook(cli);
    cout << " |" << endl;

    delete cli;
    return 1;
}

#pragma region [A7.1]

/**
 * @brief Starts a simple program to demonstrate map's usage.
 * @param cli A CLI-Tool to retrieve user inputs and print outputs.
 */
void RunContactBook(SimpleCLI* const cli)
{
    map<string, string> contactMap;

    string userInput;
    map<string, string>::iterator mapIterator;
    pair<string, string> newContact;
    while (true)
    {
        userInput = cli->GetStringInput("Enter contact's name (or 'Exit' to finish)");
        if (userInput == "Exit") { break; }
    
        mapIterator = contactMap.find(userInput);
        if (mapIterator != contactMap.end())
        {
            cli->LogMessage("Contact's number is: " + (*mapIterator).second);
            continue;
        }
    
        cli->LogWarning("The contact is not on the list");
        cli->LogMessage("Adding new contact...", false);

        newContact.first = userInput;
        userInput = cli->GetStringInput("Enter contact's number");
        newContact.second = userInput;

        contactMap.insert(newContact);
        cli->LogMessage("Contact " + newContact.first + " was succsessfully added");
    }
    
    cli->LogMessage("Final contact list:", false, true);
    for (auto i = contactMap.begin(); i != contactMap.end(); i++)
    {
        cli->LogMessage((*i).first + ": " + (*i).second, false);
    }
}

#pragma endregion [A7.1]