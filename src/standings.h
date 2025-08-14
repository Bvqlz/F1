#pragma once
#include <string>
#include <vector>
#include <optional>

struct GeneralStanding
{
    std::string position;
    std::string name;
    std::string points;
    std::optional<std::string> team; // this is not a great work around. Would be best if this was the base class and we had two extra classes to inherit this from.
    std::string code;
};

using GenData = std::vector<GeneralStanding>; // creates alias

class DriverInstance // why is this a class? can be made a struct.
{
public:
    std::string raceNum;
    std::string DOB;
    std::string page;
    std::string nationality;
};

using driverDetails = std::vector<DriverInstance>;

struct RaceInstance
{
    std::string position;
    std::string name;
    std::string status;
    std::string points;
    std::string delta;
};

using raceDetails = std::vector<RaceInstance>;