#include <iostream>
#include <array>
#include <vector>

#include <cmath>

using namespace std;

void ReadSeries();
vector<int> EraseValues(vector<int>, int);
void CopyToArray(vector<int>, int[]);

void PrintContainer(vector<int>);
void PrintContainer(int[], size_t);

int main() {
    // A3.1
    ReadSeries();

    return 1;
}

#pragma region [A3.1]

void ReadSeries() {
    // Defining required variables and structures
    vector<int> inputSeries;
    
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

vector<int> EraseValues(vector<int> v, int target) {
    for (size_t i = 0; i < v.size(); i++) {
        if (v.at(i) != target) {
            continue;
        }
        
        v.erase(v.begin() + i);
        i--;
    }

    return v;
}

void CopyToArray(vector<int> v, int a[]) {
    for (size_t i = 0; i < v.size(); i++) {
        a[i] = v.at(i);
    }
}

void PrintContainer(vector<int> v) {
    for (size_t i = 0; i < v.size(); i++) {
        cout << " |-< [" << i << "]: " << v.at(i) << endl;
    }
}

void PrintContainer(int a[], size_t size) {
    for (size_t i = 0; i < size; i++) {
        cout << " |-< [" << i << "]: " << a[i] << endl;
    }
}

#pragma endregion [A3.1]