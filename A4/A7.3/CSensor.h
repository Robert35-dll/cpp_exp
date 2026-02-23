#pragma once

#include "../A4.3/SimpleCLI.h"
#include <string>

/**
 * An abstract base class for sensor sub-classes.
 */
class CSensor
{
protected:
    unsigned int m_uiId;
    float m_fValue;

public:
    CSensor() {}
    virtual ~CSensor() {}

    virtual bool init()=0;
    virtual bool update()=0;
    virtual void iam()
    {
        SimpleCLI cli = SimpleCLI();
        cli.LogMessage("Sensor ID: " + to_string(this->m_uiId), false);
        cli.LogMessage("Value: " + to_string(this->m_fValue));
    }
};
