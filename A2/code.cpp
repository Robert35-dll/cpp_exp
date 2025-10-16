#include <iostream>
#include <string>

using namespace std;

void CalculateMenuCalories();
short AddCalories(short, int);

int main() {

    // A2.1
    CalculateMenuCalories();

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