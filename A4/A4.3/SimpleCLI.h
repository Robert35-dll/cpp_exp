#pragma once
#include <string>
#include <vector>

using namespace std;

/**
 * @brief Provides simple CLI interaction methods such as
 *        number/line inputs and formatted outputs.
 */
class SimpleCLI
{
    private:
        vector<string> MenuOptions;

        string LineIndicator    = " |";
        string InputIndicator   = "[>]";
        string OutputIndicator  = "[<]";
        string ErrorIndicator   = "[!]";
        string WarningIndicator = "[*]";

        string ExecutionDebug   = " |-<";
        string ExecutionError   = " |-<!>";
        string ExecutionWarning = " |-<*>";

        bool IsValidChoice(int choice);

        void LogWarning(string description, bool isCritical = false);
        void LogError(string description, bool isCritical = false);

    public:
        SimpleCLI()
        {
            vector<string> v;
            MenuOptions = v;
        };
        SimpleCLI(vector<string> menuOptions_)
            : MenuOptions(menuOptions_)
        {};
        
        int GetOptionChoice();
        
        int GetIntInput(string requestLine, bool isSigned = false);
        string GetStringInput(string requestLine);

        void AddOption(string newOption, int index = -1);
        void SetOptions(vector<string> newOptions);

        void RemoveOption(string option);
        void RemoveOption(int index = -1);
        void ClearOptions();
};