#pragma once
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "ftxui/component/captured_mouse.hpp"
#include "ftxui/component/component.hpp"
#include "ftxui/component/component_options.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"
#include "ftxui/screen/color.hpp"


using namespace ftxui;

class Pages
{
public:
    void ShowMenu() const;
    void ShowInput() const;
    bool ShowResults(const std::string &url) const;
    void ShowDriver(const std::string& code) const;
private:
    std::string base = "https://api.jolpi.ca/ergast/f1/";
};


