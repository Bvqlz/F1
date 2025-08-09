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

Response::Response() = default;
Response::~Response() = default;



