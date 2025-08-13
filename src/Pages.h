#pragma once
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <optional>
#include "Request.h"
#include "Response.h"

#include "ftxui/component/captured_mouse.hpp"
#include "ftxui/component/component.hpp"
#include "ftxui/component/component_options.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"
#include "ftxui/screen/color.hpp"

enum class standingType
{
    Driver, Constructor
};


using namespace ftxui;

class Pages
{
public:
    void ShowMenu();
    void ShowInput();
    bool ShowResults(const std::string &url);
    void ShowDriver(const std::string& code) const;

    template<typename T>
    GenData call(const std::string& S, std::string& header);

private:
    const std::string base = "https://api.jolpi.ca/ergast/f1/";
    const std::string driverBase = "/driverstandings/";
    const std::string constBase = "/constructorstandings/";
    standingType currentType = standingType::Driver;
    std::vector<std::string> options = {"Driver", "Constructor"};

};




