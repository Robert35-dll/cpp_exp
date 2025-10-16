#include <iostream>
#include <limits>

using namespace std;

int main() {
    // `#pragma region` is VS Code specific feature
    // to create code blocks
    #pragma region [A1.2]

    // Basically: endl = "\n"

    cout << "A1.2:" << endl;

    // cout << "Hallo Welt" << endl;
    // cout << endl;
    // cout << "!!!" << endl;
    
    // or
    cout << "Hallo Welt" << endl << endl << "!!!" << endl;
    
    // or (no comma required)
    // cout << "Hallo Welt" "\n" "\n" "!!!" << endl;

    #pragma endregion [A1.2]
    #pragma region [A1.3]
    
    cout << endl << "A1.3:" << endl;
    // Use '.' to separate decimals, not ','
    
    string input;

    float height;
    float weight;
    float BMI;

    cout << "Please enter your height (in m): ";
    getline(cin, input);
    height = stof(input);

    cout << "Please enter your weight (in kg): ";
    getline(cin, input);
    weight = stof(input);

    //* To keep it simple there're no value checks
    cout << endl << "Calculating your BMI..." << endl;
    BMI = weight / (height * height);
    cout << endl << "Your BMI is " << BMI << " kg / m^2" << endl;

    #pragma endregion [A1.3]
    #pragma region [A1.4]

    cout << endl << "A1.4:" << endl;

    // Whole numbers (simillar to unsigned versions)
    short w_small;
    int w_normal;
    long w_big;

    // Decimal numbers
    float d_normal;
    double d_precise;
    long double d_exact;

    // Chars
    char c_small;
    wchar_t c_what;
    signed char c_huh;
    unsigned char c_huh2;
    char16_t c_normal;
    char32_t c_huge;

    cout << "[*] Short (small)" << endl;
    cout << " |- Range: ["<< numeric_limits<short>::min() << "; " << numeric_limits<short>::max() << "]" << endl;
    cout << " |- Size: " << numeric_limits<short>::digits << " bits" << endl;
    cout << " |- Signed: " << numeric_limits<short>::is_signed << endl;
    cout << " |" << endl;

    cout << "[*] Int (normal)" << endl;
    cout << " |- Range: ["<< numeric_limits<int>::min() << "; " << numeric_limits<int>::max() << "]" << endl;
    cout << " |- Size: " << numeric_limits<int>::digits << " bits" << endl;
    cout << " |- Signed: " << numeric_limits<int>::is_signed << endl;
    cout << " |" << endl;

    cout << "[*] Long (big)" << endl;
    cout << " |- Range: ["<< numeric_limits<long>::min() << "; " << numeric_limits<long>::max() << "]" << endl;
    cout << " |- Size: " << numeric_limits<long>::digits << " bits" << endl;
    cout << " |- Signed: " << numeric_limits<long>::is_signed << endl;
    cout << " |" << endl;

    cout << "[*] Unsigned Long (big in one direction)" << endl;
    cout << " |- Range: ["<< numeric_limits<unsigned long>::min() << "; " << numeric_limits<unsigned long>::max() << "]" << endl;
    cout << " |- Size: " << numeric_limits<unsigned long>::digits << " bits" << endl;
    cout << " |- Signed: " << numeric_limits<unsigned long>::is_signed << endl;
    cout << " |" << endl;

    cout << "[*] Float (normal)" << endl;
    cout << " |- Range: ["<< numeric_limits<float>::min() << "; " << numeric_limits<float>::max() << "]" << endl;
    cout << " |- Size: " << numeric_limits<float>::digits << " bits" << endl;
    cout << " |- Signed: " << numeric_limits<float>::is_signed << endl;
    cout << " |" << endl;

    cout << "[*] Double (precise)" << endl;
    cout << " |- Range: ["<< numeric_limits<double>::min() << "; " << numeric_limits<double>::max() << "]" << endl;
    cout << " |- Size: " << numeric_limits<double>::digits << " bits" << endl;
    cout << " |- Signed: " << numeric_limits<double>::is_signed << endl;
    cout << " |" << endl;

    cout << "[*] Long Double (exact)" << endl;
    cout << " |- Range: ["<< numeric_limits<long double>::min() << "; " << numeric_limits<long double>::max() << "]" << endl;
    cout << " |- Size: " << numeric_limits<long double>::digits << " bits" << endl;
    cout << " |- Signed: " << numeric_limits<long double>::is_signed << endl;
    cout << " |" << endl;

    cout << "[*] Signed Char (huh = UTF7? o_O)" << endl;
    cout << " |- Range: ["<< numeric_limits<char>::min() << "; " << numeric_limits<char>::max() << "]" << endl;
    cout << " |- Size: " << numeric_limits<char>::digits << " bits" << endl;
    cout << " |- Signed: " << numeric_limits<char>::is_signed << endl;
    cout << " |" << endl;
    
    cout << "[*] Unsigned Char (normal = UTF8)" << endl;
    cout << " |- Range: ["<< numeric_limits<unsigned char>::min() << "; " << numeric_limits<unsigned char>::max() << "]" << endl;
    cout << " |- Size: " << numeric_limits<unsigned char>::digits << " bits" << endl;
    cout << " |- Signed: " << numeric_limits<unsigned char>::is_signed << endl;
    cout << " |" << endl;

    cout << "[*] Wide Char (wchar_t = huh = UTF31? o_O)" << endl;
    cout << " |- Range: ["<< numeric_limits<wchar_t>::min() << "; " << numeric_limits<wchar_t>::max() << "]" << endl;
    cout << " |- Size: " << numeric_limits<wchar_t>::digits << " bits" << endl;
    cout << " |- Signed: " << numeric_limits<wchar_t>::is_signed << endl;

    #pragma endregion [A1.4]
    #pragma region [Extra]

    // Pausing CLI window (for using w/o IDE)
    cout << endl << "Press [Enter] to exit..." << endl;
        
    // Waiting for any input (only after pressing [Enter])
    cin.ignore();

    #pragma endregion [Extra]

    return 0;
}