
#include "Request.h"
#ifdef _WIN32 // curl and ftx have a contradiction using a certain key word.
#undef DOUBLE
#endif
#include "Response.h"
#include "Pages.h"

void Pages::ShowMenu() const {
    auto screen = ScreenInteractive::TerminalOutput();

    const std::vector<std::string> entries = {
        "Open Input Form",
        "Exit",
    };
    int selected = 0;

    MenuOption option;
    option.on_enter = [&] {
        if (selected == 0) {
            ShowInput(); // Takes us to second page
        } else {
            screen.ExitLoopClosure()();
        }
    };

    auto menu = Menu(&entries, &selected, option);
    const auto renderer = Renderer(menu, [&] {
        return vbox({
            menu->Render() | center | border | size(WIDTH, EQUAL, 60) | size(HEIGHT, LESS_THAN, 15)
        }) | center;
    });

    screen.Loop(renderer);
}

void Pages::ShowInput() const
{
    auto screen = ScreenInteractive::TerminalOutput();

    std::string seasonYear; // can this block strings be moved somewhere else (perhaps class)
    std::string url;
    const std::string endpoint = "/driverstandings/"; // ternary for this ? Help decide which endpoint.

    Component seasonInput = Input(&seasonYear, "Enter a season...");
    Component backBtn = Button("Back to Menu", screen.ExitLoopClosure(), ButtonOption::Ascii());
    Component submitBtn = Button("Submit", [&] {
        // this calls our next function, passes built endpoint to display respective year standings. Our Standing page returns a bool if we want to go straight to menu
        if (ShowResults(url)) { screen.ExitLoopClosure()(); }
    }, ButtonOption::Ascii());

    auto buttons = Container::Horizontal({
        submitBtn,
        backBtn,
    });

    const auto vertComp = Container::Vertical({
        seasonInput,
        buttons,
    });

    const auto renderer = Renderer(vertComp, [&] {
        url = base + seasonYear + endpoint;
        return vbox({
            hbox(text(" Season Year : "), seasonInput->Render()),
            separator(),
            text("Created endpoint: " + url),
            separator(),
            hbox({
                submitBtn->Render(),
                backBtn->Render(),
            })
        }) | border | center;
    });

    screen.Loop(renderer);
}

bool Pages::ShowResults(const std::string &url) const
{
    auto screen = ScreenInteractive::TerminalOutput();
    bool menuBack = false;

    const Request request; // can we create a template of this? Seems generic enough
    std::unique_ptr<ResBuild> processor;
    std::string jsonResponse = request.createRequest(url);
    auto headerJson = json::parse(jsonResponse);
    const std::string header = headerJson["MRData"]["StandingsTable"]["season"].get<std::string>() + " Drivers Championship - Round " + headerJson["MRData"]["StandingsTable"]["round"].get<std::string>();
    processor = std::make_unique<DriverStandings>();
    const GenData results = processor->process(jsonResponse);

    std::vector<std::string> standingsList;
    for (const auto& driver : results) {
        standingsList.push_back(
            driver.position + ". " + driver.name + " (" + driver.team + ") - " + driver.points + " pts"
        );
    }

    int selected = 0;
    MenuOption option;
    option.on_enter = [&]
    {
        ShowDriver(results[selected].code); // when we select a driver, we display their unique info. We pass their driverId to build an endpoint.
        // if (selected){} condition not required.
    };

    auto standingsMenu = Menu(&standingsList, &selected, option);

    auto inputButton = Button("Back to Input", screen.ExitLoopClosure(), ButtonOption::Ascii());

    auto menuButton = Button("Back to Menu", [&] {
        menuBack = true; // we return this bool so that we go back straight to the menu by forcing our ShowInput page closes its own loop as well.
        screen.ExitLoopClosure()();
    }, ButtonOption::Ascii());

    auto buttonContainer = Container::Horizontal
    ({
        inputButton,
        menuButton,
    });

    const auto vertComp = Container::Vertical
    ({
        standingsMenu,
        buttonContainer,
    });

    const auto renderer = Renderer(vertComp, [&] {
        return vbox({
            text(header) | center,
            separator(),
            standingsMenu->Render() | center,
            separator(),
            hbox({
               inputButton->Render(),
               menuButton->Render(),
            }) | center,
        }) | border | size(WIDTH, EQUAL, 150) | center;
    });

    screen.Loop(renderer);
    return menuBack;
}

void Pages::ShowDriver(const std::string &code) const
{
    auto screen = ScreenInteractive::TerminalOutput();

    const std::string url = base + "drivers/" + code + "/"; // pretty similar idea here. This is generic, how can i simplify this?
    const Request request;
    std::unique_ptr<ResBuild> processor;
    std::string jsonResponse = request.createRequest(url);
    auto headerJson = json::parse(jsonResponse);
    const auto& test = headerJson["MRData"]["DriverTable"]["Drivers"][0]; //would creating alias here be wise?
    const std::string header = test["givenName"].get<std::string>() + " " + test["familyName"].get<std::string>() + "'s Statistics";
    const driverDetails results = processor->DriverDetails(jsonResponse);

    auto details_renderer = Renderer([&] {
        return vbox({
            text("Driver Number: " + results[0].raceNum),
            text("Date of Birth: " + results[0].DOB),
            text("Nationality: " + results[0].nationality),
            text("Wiki: " + results[0].page)
        });
    });

    auto standingsButton = Button("Back to Standings", screen.ExitLoopClosure(), ButtonOption::Ascii());

    const auto vertComp = Container::Vertical
    ({
        details_renderer,
        standingsButton,
    });

    const auto renderer = Renderer(vertComp, [&]
    {
        return vbox ({
            text(header) | center,
            separator(),
            details_renderer->Render() | center,
            separator(),
            hbox({
                standingsButton->Render(),
            }) | center
        }) | border | size(WIDTH, EQUAL, 65) | center;
    });
    screen.Loop(renderer);
}
