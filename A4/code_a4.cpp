#include "./A4.1/Caesar.h"
#include "./A4.3/SIMcard.h"
#include "./A4.3/SimpleCLI.h"

#include <cmath>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// A4.1 Functions
void TestCaesarCiphering();

// A4.2 Functions
void TestRectangles();

// A4.3 Functions
void ManageSIMcard();
SIMcard CreateSIMcard(SimpleCLI);
void AddContact(SimpleCLI, SIMcard);
void SearchContact(SimpleCLI, SIMcard);

int main()
{
    // A4.1
    cout << "[*] A4.1\n |" << endl;
    TestCaesarCiphering();
    cout << " |" << endl;

    // A4.2
    cout << "[*] A4.2\n |" << endl;
    TestRectangles();
    cout << " |" << endl;

    // A4.3
    ManageSIMcard();

    return 1;
}

#pragma region [A4.1]

/**
 * @brief Runs all functions of Caesar class with hard coded input.
 */
void TestCaesarCiphering()
{
    Caesar caesar;
    int customCipherKey = -5;

    string text = "Cipher me please OwO";
    string cipher = caesar.Cipher(text, customCipherKey);

    cout << "[>] Original text: " << text << endl;
    cout << "[<] Ciphered text: " << cipher << endl;

    cout << "[<] Deciphered text: ";
    cout << caesar.Decipher(cipher, customCipherKey) << endl;

    cout << "[<] Is standard cipher key used: ";
    cout << caesar.IsDecipherable(text, cipher) << endl;

    cout << "[<] Cipher key used: ";
    cout << caesar.GetCipherKey(text, cipher) << endl;
}

#pragma endregion [A4.1]
#pragma region [A4.2]

class Punkt
{
    private:
        double X, Y;
    
    public:
        Punkt(double x_ = 0, double y_ = 0)
            : X(x_), Y(y_)
        {}

        void set(double x_, double y_) { X = x_; Y = y_; }

        double getX() { return X; }
        double getY() { return Y; }
};

class Rechteck
{
    private:
        Punkt P1;
        Punkt P2;
    
    public:
        Rechteck(Punkt p1_, Punkt p2_)
            : P1(p1_), P2(p2_)
        {}

        double Flaeche()
        {
            double laenge = abs(P2.getX() - P1.getX());
            double hoehe = abs(P2.getY() - P1.getY());

            return laenge * hoehe;
        }
        double Umfang()
        {
            double laenge = abs(P2.getX() - P1.getX());
            double hoehe = abs(P2.getY() - P1.getY());
            
            return 2 * (laenge + hoehe);
        }
        unsigned int Umfang(bool inches)
        {
            double inchFaktor = inches
                ? 0.3937008
                : 1;

            return static_cast<unsigned int>(round(Umfang() * inchFaktor));
        }
};

/**
 * @brief Runs all functions to test Rechteck and Punkt classes.
 */
void TestRectangles()
{
    Punkt A, B;
    double x, y;

    cout << "[>] Koordinaten X und Y vom Punkt A: ";
    cin >> x >> y;
    A.set(x, y);

    cout << "[>] Koordinaten X und Y vom Punkt B: ";
    cin >> x >> y;
    B.set(x, y);
    
    cout << " |" << endl;
    Rechteck RE(A, B);

    cout << "[<] Die Rechteckflaeche betraegt: ";
    cout << RE.Flaeche() << endl;

    double dUmfang = RE.Umfang();
    cout << "[<] Der Umfang des Rechteckes betraegt: ";
    cout << dUmfang << endl;

    unsigned int uiUmfang = RE.Umfang(true);
    cout << "[<] Der gerundete Umfang des Rechteckes in Inches betraegt: ";
    cout << uiUmfang << endl;
}

#pragma endregion [A4.2]
#pragma region [A4.3]

/**
 * @brief Creates and manages a simple SIMcard object.
 */
void ManageSIMcard()
{
    vector<string> menuOptions = { "Create a SIMcard" };
    SimpleCLI cli = SimpleCLI(menuOptions);

    // The option is guaranteed to be 1 at this point :)
    int option = cli.GetOptionChoice();
    SIMcard simCard = CreateSIMcard(cli);

    menuOptions =
    {
        "Add Contact",
        "Search Contact number by name"
    };
    cli.SetOptions(menuOptions);

    while (option != -1)
    {
        option = cli.GetOptionChoice();

        switch (option)
        {
            case 1:
            {
                AddContact(cli, simCard);
                break;
            }
            case 2:
            {
                //! For some reason no contacts are present !
                SearchContact(cli, simCard);
                break;
            }
        }
    }

    cli.LogMessage("Finishing the program...", false, true);
}

/**
 * @brief Creates a SIMcard object.
 * @note The SIMcard has to have a 4 digit PIN.
 * @param cli: A ClI tool to retrieve inputs and give outputs by.
 * @retval A new `SIMcard` object.
 */
SIMcard CreateSIMcard(SimpleCLI cli)
{
    cli.LogWarning("Creating a new SIMcard...", false, true);
    
    int pin = 0;
    
    while (pin == 0)
    {
        pin = cli.GetIntInput("Enter a 4 digit PIN of your new SIMcard");
        if (pin % 10000 < 1000 || pin > 9999)
        {
            cli.LogError("The PIN must be a 4 digit number!", true, true);
            pin = 0;
        }
    }

    SIMcard newCard = SIMcard(pin);
    cli.LogMessage("Successfully created SIMcard :D", true);

    return newCard;
}

/**
 * @brief Adds a contact to the given SIMcard.
 * @param cli: A ClI tool to retrieve inputs and give outputs by.
 * @param card: The card to add a contact to.
 */
void AddContact(SimpleCLI cli, SIMcard card)
{
    cli.LogWarning("Adding new contact...", false, true);

    string contactName = cli.GetStringInput("Enter contact's name");
    int contactNumber = cli.GetIntInput("Enter contact's number");
    int pin = cli.GetIntInput("Enter the PIN of your card");

    bool result = card.trageEin(contactName, contactNumber, pin);
    if (!result)
    {
        cli.LogError("Incorrect PIN. Please try again.", true, true);
    }
    else
    {
        cli.LogMessage("Successfully added new contact :D", true);
    }
}

/**
 * @brief Searches a certain contact in the list of the given SIMcard.
 * @param cli: A ClI tool to retrieve inputs and give outputs by.
 * @param card: The card to search the contact of.
 */
void SearchContact(SimpleCLI cli, SIMcard card)
{
    string contactName = cli.GetStringInput("Enter contact's name");
    int pin = cli.GetIntInput("Enter the PIN of your card");

    string output;
    int result = card.sucheNummer(contactName, pin);
    switch (result)
    {
        case -1:
        {
            output = "Incorrect PIN. Please try again.";
            cli.LogError(output, true, true);
            break;
        }
        case 0:
        {
            output = "No contact with the name " + contactName + " was found :(";
            cli.LogWarning(output);
            break;
        }
        default:
        {
            output = "The " + contactName + "'s number is " + to_string(result);
            cli.LogMessage(output);
            break;
        }
    }
}

#pragma endregion [A4.3]