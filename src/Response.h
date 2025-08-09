#pragma once
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class Response
{
public:
    Response();
    ~Response();

    static void createResponse(const std::string& jsonString);
    static void createResponse2(const std::string& jsonString);
    static void createResponse3(const std::string& jsonString);

private:

};