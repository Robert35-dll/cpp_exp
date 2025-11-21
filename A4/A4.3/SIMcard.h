#pragma once
#include <string>
#include <vector>

using namespace std;

struct Eintrag
{
    string name;
    int nummer;
};

class SIMcard
{
    private:
        vector<Eintrag> Telefonbuch;
        unsigned int PIN;

    public:
        SIMcard(unsigned int pin_)
            : PIN(pin_)
        {}

        bool trageEin(string name_, int nummer_, unsigned int pin_);

        int sucheNummer(string name_, unsigned int pin_);
};
