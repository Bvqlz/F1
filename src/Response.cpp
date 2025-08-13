#include "Response.h"

GenData DriverStandings::process(const std::string &jsonString) const
{
    GenData driverStandings;
    auto responseJson = json::parse(jsonString);

    const auto& resDriver = responseJson["MRData"]["StandingsTable"]; // this can be removed

    for (const auto& driver : resDriver["StandingsLists"][0]["DriverStandings"])
    {
        driverStandings.push_back({
            driver["position"].get<std::string>(),
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

GenData RaceResults::process(const std::string &jsonString) const
{
    auto responseJson = json::parse(jsonString);
    const auto& resResult = responseJson["MRData"]["RaceTable"]["Races"][0]; //we can call the results endpoint, we want to get the first object in the array.

    std::cout << "[-- " << resResult["season"].get<std::string>() << " " << resResult["raceName"].get<std::string>() << " Results --]" <<
    " @ " << resResult["Circuit"]["circuitName"].get<std::string>() << " - Race [" << resResult["round"].get<std::string>() << "]" << std::endl;

    //responseJson["MRData"]["RaceTable"]["Races"][0]["Results"] // we can just use our resResult instead of this line to get our driver data.

    for (const auto& result : resResult["Results"])
    {
        std::cout << "[ " << result["position"].get<std::string>() << ". " << result["Driver"]["givenName"].get<std::string>()
        << " " << result["Driver"]["familyName"].get<std::string>()
        << " | " << result["status"].get<std::string>()
        << " | + " << result["points"].get<std::string>() << " pts]" << std::endl;
    }
}


