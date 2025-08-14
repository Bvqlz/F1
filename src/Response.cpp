#include "Response.h"

GenData DriverStandings::process(const std::string &jsonString) const
{
    GenData driverStandings;
    auto responseJson = json::parse(jsonString);

    const auto& resDriver = responseJson["MRData"]["StandingsTable"]; // this can be removed

    for (const auto& driver : resDriver["StandingsLists"][0]["DriverStandings"])
    {
        std::string position = "N/A";
        if (driver.contains("position")) {
            position = driver["position"].get<std::string>();
        }
        else
        {
            continue;
        }

        driverStandings.push_back({
            position,
            driver["Driver"]["givenName"].get<std::string>() + " " + driver["Driver"]["familyName"].get<std::string>(),
            driver["points"].get<std::string>(),
            driver["Constructors"][0]["name"].get<std::string>(),
            driver["Driver"]["driverId"].get<std::string>()
        });
    }

        return driverStandings;
    }

GenData ConstructorStandings::process(const std::string& jsonString) const
{
    GenData constructorStandings;
    auto responseJson = json::parse(jsonString);
    const auto& resConst = responseJson["MRData"]["StandingsTable"];

    for (const auto& constructor : resConst["StandingsLists"][0]["ConstructorStandings"])
    {
        constructorStandings.push_back({
            constructor["position"].get<std::string>(),
            constructor["Constructor"]["name"].get<std::string>(),
            constructor["points"].get<std::string>(),
            std::nullopt,
            constructor["Constructor"]["constructorId"].get<std::string>(),
        });
    }

    return constructorStandings;
}

driverDetails ResBuild::DriverDetails(const std::string & jsonString) const
{
    driverDetails driverData;
    auto responseJson = json::parse(jsonString);
    const auto& driver = responseJson["MRData"]["DriverTable"]["Drivers"][0];

    driverData.push_back({
        driver["permanentNumber"].get<std::string>(),
        driver["dateOfBirth"].get<std::string>(),
        driver["url"].get<std::string>(),
        driver["nationality"].get<std::string>(),
    });

    return driverData;
}

raceDetails ResBuild::RaceDetails(const std::string &jsonString) const
{
    raceDetails raceData;
    auto responseJson = json::parse(jsonString);

    for (const auto& race : responseJson["MRData"]["RaceTable"]["Races"][0]["Results"])
    {

        std::string delta = "N/A";

        if (race.contains("Time")) {
            delta = race["Time"]["time"].get<std::string>();
        }

        raceData.push_back({
        race["position"].get<std::string>(),
        race["Driver"]["givenName"].get<std::string>() + " " + race["Driver"]["familyName"].get<std::string>(),
        race["status"].get<std::string>(),
        race["points"].get<std::string>(),
        delta,
    });
    }

    return raceData;
}

