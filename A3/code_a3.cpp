#include <iostream>
#include <array>
#include <vector>

#include <cmath>

using namespace std;

void ReadSeries();
void PrintContainer(vector<int>);
void PrintContainer(array<int, 50>);

int main() {
    // A3.1
    ReadSeries();

    return 1;
}

#pragma region [A3.1]

void ReadSeries() {
    // Defining required variables and structures
    vector<int> inputSeries;
    array<int, 50> outputSeries;
    
    string rawInput;
    double inputNumber;
    
    // Reading maximum 50 positive ints
    while (inputSeries.size() != 5) {
        // Requesting an input
        cout << "[>] Geben Sie eine ganze positive Zahl oder -1 ein: ";
        cin >> rawInput;
        
        // Checking, whether it's a positive int
        // if not -> skip the iteration
        try {
            inputNumber = stod(rawInput);
            // Skipping the iteration upon negative values less than -1
            if (inputNumber < -1) {
                throw out_of_range("");
            }
            // or upon non-integer numbers
            //* Thanks to Zeilinger for the idea of this type check
            //* https://cplusplus.com/forum/general/41273/#msg222521
            if (inputNumber != floor(inputNumber)) {
                throw invalid_argument("");
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
            cout << "[*] Eingabe unterbrochen" << endl;
            cout << "[<] Gespeicherte Werte:" << endl;
            
            PrintContainer(inputSeries);
            
            return;
        }
        
        // Saving the input
        //* Note: floats are converted to ints automatically
        inputSeries.push_back(inputNumber);
    }
    
    // Removing all elements that equal 5 and copying all other to the array
    for (size_t i = 0; i < inputSeries.size(); i++) {
        if (inputSeries.at(i) == 5) {
            inputSeries.erase(inputSeries.begin() + i);
            i--;
            continue;
        }
        // TODO: Resize output array
        outputSeries.at(i) = inputSeries.at(i);
    }

    // Setting the stop value to break logging
    outputSeries.at(inputSeries.size()) = -1;

    PrintContainer(outputSeries);
}

void PrintContainer(vector<int> v) {
    for (size_t i = 0; i < v.size(); i++) {
        cout << " |-< [" << i << "]: " << v.at(i) << endl;
    }
}

void PrintContainer(array<int, 50> a) {
    for (size_t i = 0; i < a.size(); i++) {
        if (a.at(i) == -1) {
            break;
        }
        cout << " |-< [" << i << "]: " << a.at(i) << endl;
    }
}

#pragma endregion [A3.1]