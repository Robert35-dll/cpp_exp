#include <iostream>
#include <array>
#include <vector>

#include <cmath>

using namespace std;

// A3.1 Functions
void ReadSeries();
vector<int> EraseValues(vector<int>, int);
void CopyToArray(vector<int>, int[]);

double GetDoubleInput(string requestLine = "Geben Sie eine Gleitkommazahl ein",
                      bool isSigned = true);
void PrintContainer(vector<int>);
void PrintContainer(int[], size_t);

// A3.2 Functions and structs
struct Book {
    int id = 0;
    string name = "NotSpecified";
    int year = 1970;
};

void RunBookStore();
int GetManagementOption();
Book CreateNewBook();

int FindBookIndex(vector<Book>, string);
int FindBookIndex(vector<Book>, int);

int GetIntInput(string requestLine = "Geben Sie eine ganze Zahl ein",
                bool isSigned = true);
string GetStringInput(string requestLine = "Geben Sie einen Titel ein");

void PrintContainer(vector<Book>);

int main() {
    // A3.1
    cout << "[*] A3.1" << endl;
    ReadSeries();
    cout << " |" << endl;

    // A3.2
    cout << "[*] A3.2" << endl;
    RunBookStore();

    return 1;
}

#pragma region [A3.1]

/**
 * @brief Reads up to 50 positive ints into a vector and copies these
 *        into an array afterwards.
 * @note If max capacity is reached, all values equal 5 will be removed :)
 */
void ReadSeries() {
    // Defining required input variables and structures
    const size_t MAX_SIZE = 50;

    vector<int> inputSeries;
    double inputNumber;
    
    // Reading maximum 50 positive ints
    while (inputSeries.size() < MAX_SIZE) {
        // Requesting an input
        inputNumber = GetDoubleInput(
            "Geben Sie eine ganze positive Zahl oder -1 ein"
        );
        
        // Skipping the iteration upon negative values less than -1
        if (inputNumber < -1) {
            cout << "[!] Es muss doch eine positive Zahl sein >:(\n |" << endl;
            continue;
        }
        // or upon non-integer numbers
        //* Thanks to Zeilinger for the idea of this type check
        //* https://cplusplus.com/forum/general/41273/#msg222521
        if (inputNumber != floor(inputNumber)) {
            cout << "[!] Es muss doch eine ganze Zahl sein >:(\n |" << endl;
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

    // If nothing was put -> do nothing :)
    if (inputSeries.size() == 0) {
        cout << " |-<!> Keine Werte wurden gespeichert." << endl;
        cout << "[^] Beende das Programm." << endl;
        return;
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
 * @brief Retrieves a `double` number from the user.
 * @note This function keeps asking for input until a convertible string
 *       is provided.
 * @param requestLine: The line to request an input with.
 * @param isSigned: Whether the number has to be positive or not.
 * @retval A `double` number provided by user.
 */
double GetDoubleInput(string requestLine, bool isSigned) {
    // Defining required variables
    string rawInput;
    double numberInput;
    
    while (true) {
        // Asking for input
        cout << "[>] " << requestLine << ": ";
        cin >> rawInput;

        // Trying to convert the input to float,
        // if succeeded -> break the loop,
        // if failed -> skip the iteration
        try {
            numberInput = stof(rawInput);
            if (!isSigned && numberInput < 0) {
                throw range_error("Keine positive Zahl eingegeben.");
            }
        } catch (invalid_argument) {
            cout << "[!] Es muss doch eine Zahl sein!\n |" << endl;
            continue;
        } catch (range_error) {
            cout << "[!] Es muss doch eine positive Zahl sein!\n |" << endl;
            continue;
        }
        
        break;
    }

    return numberInput;
}

/**
 * @brief Outputs a container into CLI.
 * @note If the vector is empty, a respective message
 *       will be printed instead.
 * @param v: The vector to output values of.
 */
void PrintContainer(vector<int> v) {
    if (v.size() == 0) {
        cout << " |-<!> Es gibt nichts :(" << endl;
        return;
    }

    for (size_t i = 0; i < v.size(); i++) {
        cout << " |-< [" << i << "]: " << v.at(i) << endl;
    }
}

/**
 * @brief Outputs a container into CLI.
 * @note If the array is empty, a respective message
 *       will be printed instead.
 * @param a[]: The array to output values of.
 * @param size: The size of the array.
 */
void PrintContainer(int a[], size_t size) {
    if (size == 0) {
        cout << " |-<!> Es gibt nichts :(" << endl;
        return;
    }

    for (size_t i = 0; i < size; i++) {
        cout << " |-< [" << i << "]: " << a[i] << endl;
    }
}

#pragma endregion [A3.1]
#pragma region [A3.2]

/**
 * @brief Starts a program that operates a simple book store.
 * @note There're several options to add, remove and list saved books.
 */
void RunBookStore() {
    //* Operating process:
    //*
    //* Step 1: Ask for input of a new book     -> Step 2
    //*         or for output of stored books   -> Step 3
    //*         or for exit                     -> Step 1*
    //*         |
    //* Step 1*:Prevent future requests and exit

    //* Step 2: Create new struct object via cin
    //*         add to the store (vector)
    //*         validate input
    //*         |
    //* Step 2*:If input's wrong -> remove and go to step 2
    //*         If input's right -> go to step 1

    //* Step 3: List all available books
    //*         Ask for removal of a book (per index or name)
    //*         |
    //* Step 3*:If requested -> remove the book and go to step 1
    //*         If not       -> just go to step 1

    // Defining required input variables and structures
    vector<Book> bookStore;

    string validationOption;
    int option = 0;

    // Reading inputs and operating the store
    while (option != -1) {
        cout << " |" << endl;

        // Step 1: Asking for input or output
        option = option == 0 ? GetManagementOption() : option;

        switch (option) {
            // Step 1.1: Exiting program
            case -1: {
                cout << " |-<*> Beende das Programm" << endl;
                continue;
            }
            // Step 2: Adding a new book and validating it
            case 1: {
                cout << " |-<*> Erstelle neues Buch..." << endl;
                Book newBook = CreateNewBook();
                bookStore.push_back(newBook);

                validationOption = GetStringInput(
                    "Ist das neue Buch falsch eingetragen? [j / n]"
                );
                break;
            }
            // Step 3: Listing available books and validating them
            case 2: {
                PrintContainer(bookStore);

                if (bookStore.size() != 0) {
                    validationOption = GetStringInput(
                        "Wollen Sie ein Buch entfernen? [j / n]"
                    );
                } else {
                    validationOption = "n";
                }
                break;
            }
            default: {
                cout << "[!] Ungültige Option. ";
                cout << "Bitte prüfen Sie ihre Eingabe.\n |" << endl;

                option = 0;
                continue;
            }
        }

        // If validation failed -> do respective substeps
        if (validationOption.length() >= 1 && validationOption.at(0) != 'n') {
            // Step 2*
            // If an input's incorrect -> remove last book and go to Step 2
            if (option == 1) {
                cout << " |-<*> Entferne das Buch..." << endl;
                bookStore.pop_back();

                continue;
            }
            // Step 3*
            // If removal requested -> remove the book and go to Step 1
            if (option == 2) {
                string bookId = GetStringInput(
                    "Geben Sie den Titel oder die (ID) vom Buch ein"
                );

                // Looking for the book and removing it
                int bookIndex = FindBookIndex(bookStore, bookId);
                if (bookIndex != -1) {
                    cout << " |-<*> Entferne das Buch..." << endl;
                    bookStore.erase(bookStore.begin() + bookIndex);
                }

                option = 0;
                continue;
            }
        }

        // Returning to Step 1
        option = 0;
    }

    cout << "[^] Programm beendet" << endl;
}

/**
 * @brief Asks for a choice of certain pre-defined options.
 * @retval The number of chosen option as `int`.
 */
int GetManagementOption() {
    // Defining required input variable
    int option;

    while (true) {
        // Printing options
        cout << "[?] Was wollen Sie tun?\n |" << endl;
        cout << "[1] Neues Buch hinzufügen" << endl;
        cout << "[2] Vorhandene Bücher auflisten" << endl;
        cout << " |" << endl;
        cout << "[-1] Programm beenden" << endl;
        cout << " |" << endl;

        // Reading input,
        // if option's valid -> break the loop and return it,
        // if option's invalid -> iterate again
        option = GetIntInput();
        if (option == -1 || option == 1 || option == 2) {
            break;
        }

        cout << "[!] Bitte geben Sie eine gültige Option ein!\n |" << endl;
    }

    return option;
}

/**
 * @brief Asks for several inputs to create a new `Book` object.
 * @retval A new `Book` object.
 */
Book CreateNewBook() {
    Book newBook;
    newBook.id = GetIntInput("Geben Sie die ID vom Buch ein", false);
    newBook.name = GetStringInput("Geben Sie den Titel vom Buch ein");
    newBook.year = GetIntInput("Geben Sie das Erscheinungsjahr ein");

    return newBook;
}

/**
 * @brief Searches for a book with specified title in the given vector.
 * @note If title can be converted to an int, a respective overloaded
 *       function will be called instead.
 * @param v: The vector to search the book in.
 * @param target_name: The title of the book to seach.
 * @retval The index of the found book withing the given vector or
 *         -1, if nothing was found.
 */
int FindBookIndex(vector<Book> v, string target_name) {
    // Checking, whether the name is an ID of a book,
    // if not -> search by the name instead
    try {
        int target_id = stoi(target_name);
        return FindBookIndex(v, target_id);
    } catch (invalid_argument) {}

    cout << " |-<*> Suche das Buch nach dem Titel..." << endl;

    for (size_t i = 0; i < v.size(); i++) {
        if (v.at(i).name == target_name) {
            return i;
        }
    }

    cout << " |-<!> Kein Buch mit dem Titel '";
    cout << target_name << "' gefunden :(" << endl;
    return -1;
}

/**
 * @brief Searches for a book with specified ID in the given vector.
 * @param v: The vector to search the book in.
 * @param target_id: The ID of the book to seach.
 * @retval The index of the found book withing the given vector or
 *         -1, if nothing was found.
 */
int FindBookIndex(vector<Book> v, int target_id) {
    cout << " |-<*> Suche das Buch nach der ID..." << endl;

    for (size_t i = 0; i < v.size(); i++) {
        if (v.at(i).id == target_id) {
            return i;
        }
    }

    cout << " |-<!> Kein Buch mit der ID '";
    cout << target_id << "' gefunden :(" << endl;
    return -1;
}

/**
 * @brief Retrieves an `int` number from the user.
 * @note This function keeps asking for input until a convertible string
 *       is provided.
 * @param requestLine: The line to request an input with.
 * @param isSigned: Whether the number has to be positive or not.
 * @retval An `int` number provided by user.
 */
int GetIntInput(string requestLine, bool isSigned) {
    // Defining required input variables
    string rawInput;
    int numberInput;

    while (true) {
        // Asking for input
        cout << "[>] " << requestLine << ": ";
        cin >> rawInput;

        // Trying to convert the input to int,
        // if succeeded -> break the loop,
        // if failed -> skip the iteration
        try {
            numberInput = stoi(rawInput);
            if (!isSigned && numberInput < 0) {
                throw range_error("Keine positive Zahl eingegeben.");
            }
        } catch (invalid_argument) {
            cout << "[!] Es muss doch eine Zahl sein!\n |" << endl;
            continue;
        } catch (range_error) {
            cout << "[!] Es muss doch eine positive Zahl sein!\n |" << endl;
            continue;
        }

        break;
    }

    return numberInput;
}

/**
 * @brief Retrieves a text from the user.
 * @note This function keeps asking for input until a non-empty string
 *       is provided.
 * @param requestLine: The line to request an input with.
 * @retval A `string` line provided by user.
 */
string GetStringInput(string requestLine) {
    // Defining required input variable
    string rawInput;

    while (true) {
        // Asking for input
        cout << "[>] " << requestLine << ": ";
        cin >> rawInput;

        // Validating the string,
        // if succeeded -> break the loop,
        // if failed -> iterate again
        if (rawInput.length() >= 1 && rawInput.at(0) != ' ') {
            break;
        }

        cout << "[!] Ungültige Eingabe! Bitte versuchen Sie nochmal.\n |" << endl;
    }

    return rawInput;
}

/**
 * @brief Outputs a container into CLI.
 * @note If the vector is empty, a respective message
 *       will be printed instead.
 * @param v: The vector to output values of.
 */
void PrintContainer(vector<Book> v) {
    if (v.size() == 0) {
        cout << " |-<!> Es gibt keine Bücher :(" << endl;
        return;
    }

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