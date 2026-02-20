#include <iostream>
#include <stdexcept>
#include <string>
#include <map>
#include <vector>

#include "../A4/A4.3/SimpleCLI.h"

// Auto ID + Kind
#define Vehicle pair<string, string>
// Driver ID + Auto
#define AutoPark multimap<string, Vehicle>

using namespace std;

// A7.1 Functions
void RunContactBook(SimpleCLI* const);

// A7.2 Functions
void RunAutoPark(SimpleCLI* const);

void AddDriver(AutoPark* const, SimpleCLI* const);
void AddVehicle(AutoPark* const, SimpleCLI* const);
void AddVehicle(string* const, AutoPark* const, SimpleCLI* const);
Vehicle CreateVehicle(SimpleCLI* const);

void ListDrivers(AutoPark* const, SimpleCLI* const);
void SearchDriver(AutoPark* const, SimpleCLI* const);
void SearchVehicle(AutoPark* const, SimpleCLI* const);

void RemoveDriver(AutoPark* const, SimpleCLI* const);
void RemoveVehicle(AutoPark* const, SimpleCLI* const);

AutoPark::iterator FindDriver(string* const, AutoPark* const);
AutoPark::iterator FindVehicle(string* const, AutoPark* const);

int main()
{
    SimpleCLI* const cli = new SimpleCLI();

    // A7.1
    cout << "[*] A7.1\n |" << endl;
    RunContactBook(cli);
    cout << " |" << endl;

    // A7.2
    cout << "[*] A7.2\n |" << endl;
    RunAutoPark(cli);
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
        cli->LogMessage("Contact " +
                        newContact.first +
                        " was succsessfully added");
    }
    
    cli->LogMessage("Final contact list:", false, true);
    for (auto i = contactMap.begin(); i != contactMap.end(); i++)
    {
        cli->LogMessage((*i).first + ": " + (*i).second, false);
    }
}

#pragma endregion [A7.1]
#pragma region [A7.2]

/**
 * @brief Starts a program that operates a simple auto park.
 * @param cli: A CLI tool to retrieve inputs and give outputs by.
 */
void RunAutoPark(SimpleCLI* const cli)
{
    vector<string> menuOptions = {
        "Add new driver",
        "Add vehicle",
        "List all drivers",
        "Search driver",
        "Search vehicle",
        "Remove driver",
        "Remove vehicle"
    };
    cli->AddOption(menuOptions[0]);
    
    int option = cli->GetOptionChoice();
    AutoPark* park = new AutoPark();

    cli->SetOptions(menuOptions);
    map<int, void(*)(AutoPark* const, SimpleCLI* const)> managingOperations =
    {
        {1, AddDriver},
        {2, AddVehicle},
        {3, ListDrivers},
        {4, SearchDriver},
        {5, SearchVehicle},
        {6, RemoveDriver},
        {7, RemoveVehicle}
    };

    while (option != -1)
    {
        // Option is guaranteed to be in bounds thanks to SimpleCLI :D
        managingOperations[option](park, cli);
        
        if (park->empty())
        {
            cli->ClearOptions();
            cli->AddOption(menuOptions[0]);
        }
        else
        {
            cli->SetOptions(menuOptions);
        }
        option = cli->GetOptionChoice();
    }
}

/**
 * @brief Adds a new driver with his vehicle to the given park.
 * @note If a driver or a vehicle with provided IDs are already registered,
 *       no driver will be added.
 * @param park: The auto park to add a driver to.
 * @param cli: A CLI tool to retrieve inputs and give outputs by.
 */
void AddDriver(AutoPark* const park, SimpleCLI* const cli)
{
    string newDriverId = cli->GetStringInput("Enter new driver's ID");

    if (FindDriver(&newDriverId, park) != park->cend())
    {
        cli->LogError("Driver already exists." \
                      "Try adding new vehicle instead -_-");
        return;
    }

    try
    {
        AddVehicle(&newDriverId, park, cli);
        cli->LogMessage("Successfully added new driver!");
    }
    catch (const range_error& e)
    {
        cli->LogError(e.what());
    }
}
/**
 * @brief Adds a new vehicle to the given park.
 * @note If a vehicle with the same ID is already registered
 *       or specified driver doesn't exist,
 *       no vehicle will be added.
 * @param park: The auto park to add a vehicle to.
 * @param cli: A CLI tool to retrieve inputs and give outputs by.
 */
void AddVehicle(AutoPark* const park, SimpleCLI* const cli)
{
    string driverId = cli->GetStringInput("Enter driver's ID");

    if (FindDriver(&driverId, park) == park->cend())
    {
        cli->LogError("Driver not found. Try adding him first -_-");
        return;
    }
    
    try
    {
        AddVehicle(&driverId, park, cli);
        cli->LogMessage("Successfully added new vehicle!");
    }
    catch (const range_error& e)
    {
        cli->LogError(e.what());
    }
}
/**
 * @brief Adds a new vehicle to the given driver in the specified park.
 * @note If a vehicle with the same ID is already registered,
 *       no vehicle will be added.
 * @param driverId: The ID of a driver to add a vehicle to.
 * @param park: The auto park to add a vehicle to.
 * @param cli: A CLI tool to retrieve inputs and give outputs by.
 */
void AddVehicle(string* const driverId, AutoPark* const park, SimpleCLI* const cli)
{
    Vehicle newVehicle = CreateVehicle(cli);
    if (FindVehicle(&newVehicle.first, park) != park->end())
    {
        throw range_error("Vehicle with this ID already exists." \
                          "Check your inputs ಠ_ಠ");
    }

    park->insert({*driverId, newVehicle});
}
/**
 * @brief Creates a new vehicle object.
 * @param cli: A CLI tool to retrieve inputs and give outputs by.
 * @return A new Vehicle string pair.
 */
Vehicle CreateVehicle(SimpleCLI* const cli)
{
    string id  = cli->GetStringInput("Enter the vehicle's ID");
    string art = cli->GetStringInput("Enter the vehicle's kind " \
                                     "(coupe, sedan, van, etc.)");

    return Vehicle(id, art);
}

/**
 * @brief Lists all registered drivers with amount of their vehicles.
 * @param park: The auto park to look for drivers in.
 * @param cli: A CLI tool to retrieve inputs and give outputs by.
 */
void ListDrivers(AutoPark* const park, SimpleCLI* const cli)
{
    cli->LogMessage("Registered drivers:", false, true);
    
    int driverAmount  = 0;
    int vehicleAmount = 0;
    size_t vehicleCount = 0;

    auto i = park->begin();
    while (i != park->cend())
    {
        vehicleCount = park->count(i->first);
        
        driverAmount++;
        vehicleAmount += vehicleCount;
        
        cli->LogMessage(i->first +
                        " (" + to_string(vehicleCount) + " vehicles)",
                        false);

        // Skipping all vehicles of a driver
        i = park->upper_bound(i->first);
    }

    cli->LogMessage("Total drivers: " + to_string(driverAmount), false, true);
    cli->LogMessage("Total vehicles: " + to_string(vehicleAmount), true, true);
}
/**
 * @brief Lists information of a certain driver.
 * @param park: The auto park to look for a driver in.
 * @param cli: A CLI tool to retrieve inputs and give outputs by.
 */
void SearchDriver(AutoPark* const park, SimpleCLI* const cli)
{
    string driverId = cli->GetStringInput("Enter the driver's ID");
    if (FindDriver(&driverId, park) == park->end())
    {
        cli->LogWarning("No driver with this ID has been registered :(");
        return;
    }

    cli->LogMessage("Driver " +
                    driverId +
                    " has registered following vehicles:",
                    false, true);
    
    auto vehicles = park->equal_range(driverId);
    for (auto i = vehicles.first; i != vehicles.second; i++)
    {
        cli->LogMessage(i->second.first + " " + i->second.second, false);
    }

    cout << " |" << endl;
}
/**
 * @brief Lists information about certain vehicle.
 * @param park: The auto park to look for a vehicle in.
 * @param cli: A CLI tool to retrieve inputs and give outputs by.
 */
void SearchVehicle(AutoPark* const park, SimpleCLI* const cli)
{
    string vehicleId = cli->GetStringInput("Enter the vehicle's ID");
    auto searchResult = FindVehicle(&vehicleId, park);

    if (searchResult == park->end())
    {
        cli->LogWarning("No vehicle with this ID has been registered :(");
        return;
    }

    cli->LogMessage("ID: " + searchResult->second.first, false);
    cli->LogMessage("Kind: " + searchResult->second.second, false);
    cli->LogMessage("Driver: " + searchResult->first, false);

    cout << " |" << endl;
}

/**
 * @brief Removes a driver with all his vehicles.
 * @param park: The auto park to remove a driver from.
 * @param cli: A CLI tool to retrieve inputs and give outputs by.
 */
void RemoveDriver(AutoPark* const park, SimpleCLI* const cli)
{
    string driverId = cli->GetStringInput("Enter the driver's ID");
    if (FindDriver(&driverId, park) == park->end())
    {
        cli->LogWarning("No driver with this ID has been registered :(");
        return;
    }

    auto driverVehicles = park->equal_range(driverId);
    park->erase(driverVehicles.first, driverVehicles.second);

    cli->LogMessage("Driver has been successfully removed.");
}
/**
 * @brief Removes a vehicle of a certain driver.
 * @note If the last vehicle of a driver has been removed,
 *       the driver itself will be removed too.
 * @param park: The auto park to remove a vehicle from.
 * @param cli: A CLI tool to retrieve inputs and give outputs by.
 */
void RemoveVehicle(AutoPark* const park, SimpleCLI* const cli)
{
    string vehicleId = cli->GetStringInput("Enter the vehicle's ID");
    auto searchResult = FindVehicle(&vehicleId, park);

    if (searchResult == park->end())
    {
        cli->LogWarning("No vehicle with this ID has been registered :(");
        return;
    }
    
    park->erase(searchResult);

    cli->LogMessage("Vehicle has been successfully removed.");
}

/**
 * @brief Searches for a certain driver in the given park.
 * @param driverId: The ID of a driver to search for.
 * @param park: The auto park to search a driver in.
 * @return An iterator to the first found occurrence of
 *         the given driver's ID. If no ID was found, this
 *         will be equal to park.end() iterator.
 */
AutoPark::iterator FindDriver(string* const driverId, AutoPark* const park)
{
    return park->find(*driverId);
}
/**
 * @brief Searches for a certain vehicle in the given park.
 * @param vehicleId: The ID of a vehicle to search for.
 * @param park: The auto park to search a vehicle in.
 * @return An iterator to the first found occurrence of
 *         the given vehicle's driver's ID. If no ID was found, this
 *         will be equal to park.end() iterator.
 */
AutoPark::iterator FindVehicle(string* const vehicleId, AutoPark* const park)
{
    AutoPark::iterator i = park->begin();
    for (; i != park->end(); i++)
    {
        if (i->second.first != *vehicleId) continue;

        return i;
    }

    return i;
}

#pragma endregion [A7.2]
