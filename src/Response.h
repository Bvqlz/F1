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
};

// trying virtual functions

class ResBuild
{
public:
    virtual ~ResBuild() = default;
    virtual void process(const std::string& jsonString) const = 0; // this class is now abstract due to this virtual func.
};

class DriverStandings : public ResBuild
{
public:
    void process(const std::string& jsonString) const override;
};

class ConstructorStandings : public ResBuild
{
public:
    void process(const std::string& jsonString) const override;
};

class RaceResults : public ResBuild
{
public:
    void process(const std::string& jsonString) const override;
};

