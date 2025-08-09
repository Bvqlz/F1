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

private:

};