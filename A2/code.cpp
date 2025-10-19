#include <iostream>
#include <string>

using namespace std;

void CalculateMenuCalories();
short AddCalories(short, int);

void RunCalculator();
float GetNumberInput(string requestLine="Eingabe (Zahl):");
char GetOperatorInput(string requestLine="Eingabe (Operator):");
float Calculate(float, float, char);

int main() {

    // A2.1
    CalculateMenuCalories();

    // A2.2
    RunCalculator();

    return 0;
}

#pragma region [A2.1]

/**
 * @brief - Solution to the A2.1 exercise where a simple calories calculation
 *          has to be preformed.
 */
void CalculateMenuCalories() {
    // Defining required variables
    short calories = 0;
    unsigned char option = 0;

    // Requesting input
    cout << "[?] Such dir was aus:" << endl;
    cout << "[1] - Schnitzel\n" "[2] - Pizza\n" "[3] - Kebab\n" " |" << endl;
    cout << "[>] Deine Auswahl: ";

    // Reading the first char (ASCII-Code of a number)
    cin >> option;
    // and converting it into an actual number
    option -= '0';
    
    // If the first option is invalid, break the process
    if (1 > option || option > 3) {
        cout << "[!] Gibt's heute nicht >:(" << endl;
        return;
    }

    // Otherwise adding calories according to the choice
    calories = AddCalories(calories, option);

    // Requesting input again
    cout << " |\n" "[?] Mit Soße?" << endl;
    cout << "[1] - Ketchup\n" "[2] - Mayo\n" "[3] - Nein\n" " |" << endl;
    cout << "[>] Deine Auswahl: ";

    // Reading one more char (ASCII-Code of a number) and converting it
    cin >> option;
    option -= '0';

    // This reading will give the leftover from the first one
    // since cin has a char[] buffer for the entire input
    // option = cin.get();

    // Adding calories one more time
    calories = AddCalories(calories, option);

    // and finishing the process
    cout << " |\n" "[>] Deine Menu enthält " << calories << " Kalorien" << endl;
}

/**
 * @brief Adds calories to the current amount depending on given option.
 * @note This is a supporting function for `CalculateMenuCalories()`.
 * @param calories: The current amount of calories to add to.
 * @param option: The chosen menu's option.
 * @retval The updated (increased) amount of calories or the same one,
 *         if the option is invalid.
 */
short AddCalories(short calories, int option) {
    // Since there're 2x3 options, it's possible to
    // spare thee of them by adding an if-statement
    // in each case (ik it's a very hard coded
    // solution tho) X(
    switch (option) {
        case 1: {
            calories += calories < 600
                ? 900
                : 30;
            break;
        }
        case 2: {
            calories += calories < 600
                ? 870
                : 50;
            break;
        }
        case 3: {
            calories += calories < 600
                ? 600
                : 0;
            break;
        }
    }

    return calories;
}

#pragma endregion [A2.1]
#pragma region [A2.2]

/**
 * @brief Asks for required number and operator inputs
 *        to perform a simple mathematical operations: +, -, * and /.
 */
void RunCalculator() {
    float a = GetNumberInput("Eingabe Zahl1:");
    char o = GetOperatorInput("Eingabe Operator:");
    float b = GetNumberInput("Eingabe Zahl2:");

    float result = Calculate(a, b, o);
    cout << "[>] Ergebnis: " << result << endl;
}

/**
 * @brief Retrieves a float number from the user.
 * @note This function keeps asking for input until a convertible string
 *       is provided.
 * @param requestLine: The line to request an input with.
 * @retval A float number provided by user.
 */
float GetNumberInput(string requestLine) {
    // Defining required variables
    string rawInput;
    float inputNumber;

    // Asking for input
    cout << "[<] " << requestLine << ' ';

    while (true) {
        // Reading the next input
        //* Note: Cast automatically to a number of the target variable's type
        cin >> rawInput;

        // Trying to convert the input to float,
        // if succeeded -> breaking the loop and returning the number,
        // if failed -> asking for input again
        try {
            inputNumber = stof(rawInput);
            break;
        } catch (invalid_argument) {
            cout << "[!] Bitte eine Zahl eingeben!" << endl;
            cout << "[<] " << requestLine << ' ';
        }
        // Alternative catch according to
        // https://cplusplus.com/reference/stdexcept/invalid_argument/
        // could be like this: (idk why tbh :<)
        // catch (const std::invalid_argument& ia) {
        //     std::cerr << "Invalid argument: " << ia.what() << '\n';
        // }
    }

    return inputNumber;
}

/**
 * @brief Retrieves a char of a valid operator from user.
 * @note This function keeps asking for input until a valid char is provided.
 * @param requestLine: The line to request an input with.
 * @retval An operator's char provided by user.
 */
char GetOperatorInput(string requestLine) {
    // Defining required variables
    string rawInput;
    char inputOperator;

    // Asking for input
    cout << "[<] " << requestLine << ' ';

    while (true) {
        // Reading the next input
        //* Note: Cast automatically to a number of the target variable's type
        cin >> rawInput;

        // Validating the input by checking whether:
        // 1) it's a single char
        if (rawInput.length() != 1) {
            cout << "[!] Bitte den Operator als ein Zeichen eingeben!" << endl;
            cout << "[<] " << requestLine << ' ';
            
            continue;
        }
        
        // 2) it's a valid operator,
        // if succeeded -> breaking the loop and returning the operator's char,
        // if failed -> asking for input again
        if (rawInput[0] == '+' ||
            rawInput[0] == '-' ||
            rawInput[0] == '*' ||
            rawInput[0] == '/') {
            inputOperator = rawInput[0];

            break;
        } else {
            cout << "[!] Bitte einen Operator eingeben! (+, -, *, /)" << endl;
            cout << "[<] " << requestLine << ' ';

            continue;
        }
    }

    return inputOperator;
}

/**
 * @brief Performs the given operation on two given numbers.
 * @note Valid operations are: +, -, *, /. If an invalid operation is given,
 *       the result is set to 0.
 * @param a: The first number of the operation (e.g numerator in division).
 * @param b: The second number of the operation (e.g. denominator in division).
 * @param operation: The sign of the operation to perform. 
 * @retval A float number of the operation's result or 0, if an invalid
 *         operation was specified.
 */
float Calculate(float a, float b, char operation) {
    // Defining required variables
    float calculation = 0.0;

    // Seeking the specified operation,
    // if failed -> leaving the default value for the result
    switch (operation) {
        case '+': {
            calculation = a + b;
            break;
        }
        case '-': {
            calculation = a - b;
            break;
        }
        case '*': {
            calculation = a * b;
            break;
        }
        case '/': {
            //* Don't forget an edge case ಠ_ಠ
            if (b != 0) {
                calculation = a / b;
            } else {
                cout << "[!] Man darf nicht durch 0 dividieren!" << endl;
            }
            break;
        }
        default: {
            cout << "[!] Ungültiger Operator. Kann nicht rechnen!" << endl;
        }
    }

    return calculation;
}

#pragma endregion [A2.2]