//
// Created by ericv on 8/9/2025.

#include "Response.h"

void Response::createResponse(const std::string &jsonString)
{
    auto responseJson = json::parse(jsonString);

     for (const auto& driver : responseJson["MRData"]["StandingsTable"]["StandingsLists"][0]["DriverStandings"])
     {
         std::cout << "Driver Name: " << driver["Driver"]["givenName"].get<std::string>() + " " + driver["Driver"]["familyName"].get<std::string>() << std::endl;
         std::cout << "Team Name: " << driver["Constructors"][0]["name"].get<std::string>() << std::endl;
         std::cout << "Racing Number: " << driver["Driver"]["permanentNumber"].get<std::string>() << std::endl;
         std::cout << "Nationality: " << driver["Driver"]["nationality"].get<std::string>() << std::endl;
         std::cout << "Current Position: " << driver["position"].get<std::string>() + " | " + " Points: " << driver["points"].get<std::string>() << std::endl;
         std::cout << "-----------------------------------------------------------------------" << std::endl;
     }
}

void Response::createResponse2(const std::string& jsonString)
{
    auto responseJson = json::parse(jsonString);
    const auto& resResult = responseJson["MRData"]["RaceTable"]["Races"][0]; //we can call the results endpoint, we want to get the first object in the array.

    std::cout << "[-- " << resResult["season"].get<std::string>() << " " << resResult["raceName"].get<std::string>() << " Results --]";
    std::cout << " @ " << resResult["Circuit"]["circuitName"].get<std::string>() << " - Race [" << resResult["round"].get<std::string>() << "]" << std::endl;



    //responseJson["MRData"]["RaceTable"]["Races"][0]["Results"] // we can just use our resResult instead of this line to get our driver data.

    for (const auto& result : resResult["Results"])
    {
        std::cout << "[ " << result["position"].get<std::string>() + ". " + result["Driver"]["givenName"].get<std::string>()
        + " " + result["Driver"]["familyName"].get<std::string>();
        std::cout << " | " << result["status"].get<std::string>();
        std::cout << " | + " << result["points"].get<std::string>() << " pts]" << std::endl;
        //std::cout << result["Constructor"]["name"].get<std::string>();
    }
}


Response::Response() = default;
Response::~Response() = default;

void Response::createResponse3(const std::string &jsonString)
{
    auto responseJson = json::parse(jsonString);
    const auto& resTeam = responseJson["MRData"]["StandingsTable"];

    std::cout << "[-- " << resTeam["season"].get<std::string>() << " Constructors Championship - Round "
    << resTeam["round"].get<std::string>() << " --]" << std::endl;

    //responseJson["MRData"]["StandingsTable"]["StandingsLists"][0]["ConstructorStandings"]

    for (const auto& team : resTeam["StandingsLists"][0]["ConstructorStandings"])
    {
        std::cout << "[ " << team["position"].get<std::string>() << ". ";
        std::cout << team["Constructor"]["name"].get<std::string>() << " | ";
        std::cout << team["points"].get<std::string>() << " pts | ";
        std::cout << team["Constructor"]["nationality"].get<std::string>() << "]" << std::endl;;
    }
}


