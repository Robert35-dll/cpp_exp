#pragma once

#include "./CSensor.h"
#include "../A4.3/SimpleCLI.h"

#include <string>

class CTemSen : public virtual CSensor
{
public:
    // Base constructor is called automatically w/o arguments :D
    CTemSen() {}
    ~CTemSen() {}

    bool init() override
    {
        this->m_uiId = std::rand() % 100;

        SimpleCLI cli;
        cli.LogMessage(to_string(this->m_uiId) + " wurde initialisiert", false);

        return true;
    }
    bool update() override
    {
        this->m_fValue = std::rand() % 100;

        return true;
    }
};
