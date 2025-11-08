#include "./A4.1/Caesar.h"

#include <iostream>
#include <cmath>

using namespace std;

// A4.1 Functions
void TestCaesarCiphering();

// A4.2 Functions
void TestRectangles();

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

    return 1;
}

#pragma region [A4.1]

/**
 * @brief Runs all functions of Caesar class with hard coded input.
 */
void TestCaesarCiphering()
{
    Caesar caesar;
    string text = "Cipher me please OwO";
    string cipher = caesar.Cipher(text, -5);

    cout << "[>] Original text: " << text << endl;
    cout << " |-<*> Ciphered text: " << cipher << endl;

    cout << " |-<*> Deciphered text: ";
    cout << caesar.Decipher(cipher, -5) << endl;

    cout << " |-<?> Is standard cipher key used: ";
    cout << caesar.IsDecipherable(text, cipher) << endl;

    cout << " |-<*> Cipher key used: ";
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
    
    cout << "\n |" << endl;
    Rechteck RE(A, B);

    cout << "[<] Die Rechteckflaeche betraegt: ";
    cout << RE.Flaeche();

    double dUmfang = RE.Umfang();
    cout << "[<] Der Umfang des Rechteckes betraegt: ";
    cout << dUmfang;

    unsigned int uiUmfang = RE.Umfang(true);
    cout << "[<] Der gerundete Umfang des Rechteckes in Inches betraegt: ";
    cout << uiUmfang << endl;
}

#pragma endregion [A4.2]