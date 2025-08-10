//
// Created by ericv on 8/9/2025.

#include "Response.h"

void Response::createResponse(const std::string &jsonString)
{
    auto responseJson = json::parse(jsonString);

    const auto& resDriver = responseJson["MRData"]["StandingsTable"];

    std::cout << "[-- " << resDriver["season"].get<std::string>() << " Drivers Championship - Round "
    << resDriver["round"].get<std::string>() << " --]" << std::endl;

    //responseJson["MRData"]["StandingsTable"]["StandingsLists"][0]["DriverStandings"]

     for (const auto& driver : resDriver["StandingsLists"][0]["DriverStandings"])
     {
         std::cout << "[ " << driver["position"].get<std::string>() << ". "
        << driver["Driver"]["givenName"].get<std::string>() << " " << driver["Driver"]["familyName"].get<std::string>()  << " | "
        << driver["points"].get<std::string>() << " pts | "
        << driver["Constructors"][0]["name"].get<std::string>() << " | "
        << driver["Driver"]["nationality"].get<std::string>() << "]" << std::endl;
     }
}

void Response::createResponse2(const std::string& jsonString)
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
        //std::cout << result["Constructor"]["name"].get<std::string>();
    }
}

void Response::createResponse3(const std::string &jsonString)
{
    auto responseJson = json::parse(jsonString);
    const auto& resTeam = responseJson["MRData"]["StandingsTable"];

    std::cout << "[-- " << resTeam["season"].get<std::string>() << " Constructors Championship - Round "
    << resTeam["round"].get<std::string>() << " --]" << std::endl;

    //responseJson["MRData"]["StandingsTable"]["StandingsLists"][0]["ConstructorStandings"]

    for (const auto& team : resTeam["StandingsLists"][0]["ConstructorStandings"])
    {
        std::cout << "[ " << team["position"].get<std::string>() << ". "
        << team["Constructor"]["name"].get<std::string>() << " | "
        << team["points"].get<std::string>() << " pts | "
        << team["Constructor"]["nationality"].get<std::string>() << "]" << std::endl;;
    }
}

Response::Response() = default;
Response::~Response() = default;

void DriverStandings::process(const std::string &jsonString) const
{
    auto responseJson = json::parse(jsonString);

    const auto& resDriver = responseJson["MRData"]["StandingsTable"];

    std::cout << "[-- " << resDriver["season"].get<std::string>() << " Drivers Championship - Round "
    << resDriver["round"].get<std::string>() << " --]" << std::endl;

    //responseJson["MRData"]["StandingsTable"]["StandingsLists"][0]["DriverStandings"]

    for (const auto& driver : resDriver["StandingsLists"][0]["DriverStandings"])
    {
        std::cout << "[ " << driver["position"].get<std::string>() << ". "
       << driver["Driver"]["givenName"].get<std::string>() << " " << driver["Driver"]["familyName"].get<std::string>()  << " | "
       << driver["points"].get<std::string>() << " pts | "
       << driver["Constructors"][0]["name"].get<std::string>() << " | "
       << driver["Driver"]["nationality"].get<std::string>() << "]" << std::endl;
    }
}

void ConstructorStandings::process(const std::string &jsonString) const
{
    auto responseJson = json::parse(jsonString);
    const auto& resTeam = responseJson["MRData"]["StandingsTable"];

    std::cout << "[-- " << resTeam["season"].get<std::string>() << " Constructors Championship - Round "
    << resTeam["round"].get<std::string>() << " --]" << std::endl;

    //responseJson["MRData"]["StandingsTable"]["StandingsLists"][0]["ConstructorStandings"]

    for (const auto& team : resTeam["StandingsLists"][0]["ConstructorStandings"])
    {
        std::cout << "[ " << team["position"].get<std::string>() << ". "
        << team["Constructor"]["name"].get<std::string>() << " | "
        << team["points"].get<std::string>() << " pts | "
        << team["Constructor"]["nationality"].get<std::string>() << "]" << std::endl;;
    }
}

void RaceResults::process(const std::string &jsonString) const
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