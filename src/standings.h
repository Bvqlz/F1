#pragma once
#include <string>
#include <vector>

struct GeneralStanding
{
    std::string position;
    std::string name;
    std::string points;
    std::string team;
    std::string code;
};

using GenData = std::vector<GeneralStanding>; // creates alias

class DriverInstance
{
public:
    std::string raceNum;
    std::string DOB;
    std::string page;
    std::string nationality;
};

using driverDetails = std::vector<DriverInstance>;