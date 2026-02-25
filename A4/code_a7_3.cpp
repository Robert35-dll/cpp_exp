#include "./A7.3/CTemSen.h"
#include "./A7.3/CSpeedSen.h"
#include "./A7.3/CDistSen.h"
#include "./A4.3/SimpleCLI.h"

#include <ctime>
#include <vector>
#include <memory>

using namespace std;

int main()
{
    // Random seed should be set once for the whole program
    std::srand(std::time(0));
    
    SimpleCLI cli;
    cli.LogWarning("A7.3", true, true);

    shared_ptr<CTemSen>   t1 = make_shared<CTemSen>();
    shared_ptr<CTemSen>   t2 = make_shared<CTemSen>();
    shared_ptr<CSpeedSen> s1 = make_shared<CSpeedSen>();
    shared_ptr<CSpeedSen> s2 = make_shared<CSpeedSen>();
    shared_ptr<CDistSen>  d1 = make_shared<CDistSen>();
    shared_ptr<CDistSen>  d2 = make_shared<CDistSen>();

    // Polymorphic classes can be stored in one container
    // by referencing the base class
    vector<shared_ptr<CSensor>> sensors;
    sensors.push_back(t1);
    sensors.push_back(t2);
    sensors.push_back(s1);
    sensors.push_back(s2);
    sensors.push_back(d1);
    sensors.push_back(d2);

    cli.LogMessage("Initializing sensors...", false, true);
    for (auto &sensor : sensors) { sensor.get()->init(); }
    cli.InsertLineBreak();

    cli.LogMessage("Updating values...", false, true);
    for (auto &sensor : sensors) { sensor.get()->update(); }
    cli.InsertLineBreak();

    cli.LogMessage("Checking sensors' setup...", false, true);
    for (auto &sensor : sensors) { sensor.get()->iam(); }

    cli.InsertLineBreak(true);

    return 1;
}
