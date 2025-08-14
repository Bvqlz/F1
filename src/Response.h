#pragma once
#include <iostream>
#include <nlohmann/json.hpp>
#include "standings.h"

using json = nlohmann::json;

class ResBuild
{
public:
    virtual ~ResBuild() = default;
    virtual GenData process(const std::string& jsonString) const = 0; // this class is now abstract due to this virtual func.
    driverDetails DriverDetails(const std::string& jsonString) const;
    raceDetails RaceDetails(const std::string& jsonString) const;
};

class DriverStandings : public ResBuild
{
public:
    GenData process(const std::string& jsonString) const override;
};

class ConstructorStandings : public ResBuild
{
public:
    GenData process(const std::string& jsonString) const override;
};






