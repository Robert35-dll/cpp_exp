#include <iostream>
#include <array>
#include <vector>

#include <cmath>

using namespace std;

// A3.1 Functions
void ReadSeries();
vector<int> EraseValues(vector<int>, int);
void CopyToArray(vector<int>, int[]);

void PrintContainer(vector<int>);
void PrintContainer(int[], size_t);

// A3.2 Functions

struct Book {
    int id = 0;
    string name = "NotSpecified";
    int year = 1970;
};

void RunBookStore();
int GetManagementOption();
Book CreateNewBook();
int GetNumberInput(string requestLine = "Geben Sie eine Zahl ein",
                   bool isSigned = true);
string GetStringInput(string requestLine = "Geben Sie einen Titel ein");

void PrintContainer(vector<Book>);

int main() {
    // A3.1
    cout << "[*] A3.1\n |" << endl;
    ReadSeries();

    // A3.2
    cout << "[*] A3.2\n |" << endl;
    RunBookStore();

    return 1;
}

#pragma region [A3.1]

void ReadSeries() {
    // Defining required input variables and structures
    const size_t MAX_SIZE = 50;

    vector<int> inputSeries;
    
    string rawInput;
    double inputNumber;
    
    // Reading maximum 50 positive ints
    while (inputSeries.size() < MAX_SIZE) {
        // Requesting an input
        cout << "[>] Geben Sie eine ganze positive Zahl oder -1 ein: ";
        cin >> rawInput;
        
        // Checking, whether it's a positive int
        // if not -> skip the iteration
        try {
            inputNumber = stod(rawInput);
            // Skipping the iteration upon negative values less than -1
            if (inputNumber < -1) {
                throw out_of_range("Eingabe manuell unterbrochen.");
            }
            // or upon non-integer numbers
            //* Thanks to Zeilinger for the idea of this type check
            //* https://cplusplus.com/forum/general/41273/#msg222521
            if (inputNumber != floor(inputNumber)) {
                throw invalid_argument("int wurde erwartet aber float bekommen.");
            }
        } catch (invalid_argument) {
            cout << "[!] Es muss doch eine ganze Zahl sein >:(" << endl;
            continue;
        } catch (out_of_range) {
            cout << "[!] Es muss doch eine positive Zahl sein >:(" << endl;
            continue;
        }
        
        // Printing converted value (for debug's sake)
        cout << " |-< Eingelesene Zahl: " << inputNumber << endl;
        
        // Breaking inputs upon receiving -1 and logging saved values
        if (inputNumber == -1) {
            cout << " |-<!> Eingabe unterbrochen" << endl;
            cout << "[<] Gespeicherte Werte:" << endl;
            
            PrintContainer(inputSeries);
            
            break;
        }
        
        // Saving the input
        //* Note: floats are converted to ints automatically
        inputSeries.push_back(inputNumber);
    }
    
    // Removing all elements that equal maximum size, if vector is full
    if (inputSeries.size() == MAX_SIZE) {
        cout << " |-<*> Entferne Werte gleich 5" << endl;
        // This might become more efficient with pointers yet to be learned
        inputSeries = EraseValues(inputSeries, 5);
    }

    // Defining the output array and copying values into it
    int outputSeries[inputSeries.size()];

    cout << " |-<*> Kopiere Werte aus dem Vektor in einen Array" << endl;
    CopyToArray(inputSeries, outputSeries);

    // Finally printing the output array
    cout << "[<] Kopierte Werte:" << endl;
    PrintContainer(outputSeries, inputSeries.size());
}

/**
 * @brief Removes certain value from a vector.
 * @note This function might work more efficient
 *       using pointers yet to be learned.
 * @param v: The vector to remove values from.
 * @param target: The value to remove.
 * @retval A vector without specified values.
 */
vector<int> EraseValues(vector<int> v, int target) {
    // Iterating through the vector
    for (size_t i = 0; i < v.size(); i++) {
        // Skipping non-target values
        if (v.at(i) != target) {
            continue;
        }
        
        // and removing the right ones
        //* Note: removing a value shrinks the vector by 1
        v.erase(v.begin() + i);
        i--;
    }

    return v;
}

/**
 * @brief Writes values from a vector into an array.
 * @note The array is to be assumed to be of the same length as the vector.
 * @param v: The vector to copy values from.
 * @param a[]: The array to copy values into.
 */
void CopyToArray(vector<int> v, int a[]) {
    for (size_t i = 0; i < v.size(); i++) {
        a[i] = v.at(i);
    }
}

/**
 * @brief Outputs a container into CLI.
 * @param v: The vector to output values of.
 */
void PrintContainer(vector<int> v) {
    for (size_t i = 0; i < v.size(); i++) {
        cout << " |-< [" << i << "]: " << v.at(i) << endl;
    }
}

/**
 * @brief Outputs a container into CLI.
 * @param a[]: The array to output values of.
 * @param size: The size of the array.
 */
void PrintContainer(int a[], size_t size) {
    for (size_t i = 0; i < size; i++) {
        cout << " |-< [" << i << "]: " << a[i] << endl;
    }
}

#pragma endregion [A3.1]
#pragma region [A3.2]

void RunBookStore() {
    //* Step 1: Ask for input of a new book
    //*         or for output of stored books
    //*         or for exit

    //* Step 2: If input -> create new struct object via cin
    //*                     add to the store (vector)
    //*                     validate input
    //*         If input's wrong -> remove and repeat step 2
    //*         If input's right -> repeat step 1

    //* Step 3: If output -> ask for removal of a book (via index or name)
    //*         If requested -> remove the book and repeat step 1

    vector<Book> bookStore;

    // Step 1: Asking for input or output
    string validationOption;
    int option = 0;

    while (option != -1) {
        option = option == 0 ? GetManagementOption() : option;

        switch (option) {
            case -1: {
                cout << " |-<*> Beende das Programm" << endl;
                continue;
            }
            // Step 2: Adding a new book
            case 1: {
                cout << " |-<*> Erstelle neues Buch..." << endl;
                Book newBook = CreateNewBook();
                bookStore.push_back(newBook);
                validationOption = GetStringInput(
                    "[?] Ist das neue Buch falsch eingetragen? [j / n]"
                );
                break;
            }
            // Step 3: Listing available books
            case 2: {
                PrintContainer(bookStore);
                validationOption = GetStringInput(
                    "[?] Wollen Sie ein Buch entfernen? [j / n]"
                );
                break;
            }
            default: {
                cout << "[!] Ungültige Option. ";
                cout << "Bitte prüfen Sie ihre Eingabe.\n |" << endl;

                option = 0;
                continue;
            }
        }

        // If an input's incorrect -> remove last book and ask for input again
        if (validationOption.length() >= 1 && validationOption.at(0) != 'n') {
            cout << " |-<*> Entferne das Buch..." << endl;

            if (option == 1) {
                bookStore.pop_back();
                
                option = 1;
            }
            if (option == 2) {
                // TODO: Remove specific book
            }
            continue;
        }

        option = 0;
    }
}

int GetManagementOption() {
    int option;
    while (true) {
        cout << "[>] Was wollen Sie tun?\n |" << endl;
        cout << "[1] Neues Buch hinzufügen" << endl;
        cout << "[2] Vorhandene Bücher auflisten" << endl;
        cout << " |" << endl;
        cout << "[-1] Programm beenden" << endl;
        cout << " |" << endl;

        option = GetNumberInput();
        if (option == -1 || option == 1 || option == 2) {
            break;
        }
        
        cout << "[!] Bitte geben Sie eine gültige Option ein!\n |" << endl;
    }

    return option;
}

Book CreateNewBook() {
    Book newBook;
    newBook.id = GetNumberInput("Geben Sie die ID vom Buch ein", false);
    newBook.name = GetStringInput("Geben Sie den Titel vom Buch ein");
    newBook.year = GetNumberInput("Geben Sie das Erscheinungsjahr ein");

    return newBook;
}

int GetNumberInput(string requestLine, bool isSigned) {
    string rawInput;
    int numberInput;
    
    while (true) {
        cout << "[<] " << requestLine << ": ";
        cin >> rawInput;

        try {
            numberInput = stoi(rawInput);
            if (!isSigned && numberInput < 0) {
                throw range_error("Keine positive Zahl eingegeben.");
            }
        } catch (invalid_argument) {
            cout << "[!] Es muss doch eine Zahl sein!\n |" << endl;
        } catch (range_error) {
            cout << "[!] Es muss doch eine positive Zahl sein!\n |" << endl;
        }
        
        break;
    }

    return numberInput;
}

string GetStringInput(string requestLine) {
    string rawInput;

    while (true) {
        cout << "[<] " << requestLine << ": ";
        cin >> rawInput;

        if (rawInput.length() >= 1 && rawInput.at(0) != ' ') {
            break;
        }

        cout << "[!] Ungültige Eingabe! Bitte versuchen Sie nochmal.\n |" << endl;
    }

    return rawInput;
}

void PrintContainer(vector<Book> v) {
    Book iBook;
    for (size_t i = 0; i < v.size(); i++) {
        iBook = v.at(i);

        cout << " |-< [" << i << "]: ";
        cout << iBook.name << " - ";
        cout << iBook.year << " - ";
        cout << '(' << iBook.id << ')' << endl;
    }
}

#pragma endregion [A3.2]