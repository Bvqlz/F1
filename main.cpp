#include "src/Request.h"
#include "src/Response.h"

#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>

#include <nlohmann/json.hpp>
#include <vector>
#include <string>

using namespace ftxui;
using json = nlohmann::json;

int main() {
    // 1. Fetch JSON using your existing Request class
    Request request;
    int year = 2025;
    std::string endpoint = "driverstandings/";
    std::string jsonResponse = request.createRequest(year, endpoint);

    // 2. Parse into a vector of strings for FTXUI
    json responseJson = json::parse(jsonResponse);
    std::vector<std::string> driver_list;

    for (const auto& driver : responseJson["MRData"]["StandingsTable"]["StandingsLists"][0]["DriverStandings"]) {
        std::string line = driver["position"].get<std::string>() + ". " +
                           driver["Driver"]["givenName"].get<std::string>() + " " +
                           driver["Driver"]["familyName"].get<std::string>() + " | " +
                           driver["points"].get<std::string>() + " pts | " +
                           driver["Constructors"][0]["name"].get<std::string>();
        driver_list.push_back(line);
    }

    // 3. Build FTXUI menu
    int selected = 0;
    auto menu = Menu(&driver_list, &selected);

    auto renderer = Renderer(menu, [&] {
        return vbox({
            text("F1 " + std::to_string(year) + " Driver Standings") | bold | center,
            separator(),
            menu->Render(),
            separator(),
            text("Selected: " + driver_list[selected]) | center
        }) | border;
    });

    // 4. Run UI
    auto screen = ScreenInteractive::FitComponent();
    screen.Loop(renderer);

    return 0;
}
