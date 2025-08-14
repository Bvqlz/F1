#ifdef _WIN32 // curl and ftx have a contradiction using a certain key word.
#undef DOUBLE
#endif
#include "Pages.h"

template<typename T>
GenData Pages::call(const std::string& S, std::string& header)
{
    const Request request;
    std::unique_ptr<ResBuild> processor;
    std::string jsonResponse = request.createRequest(S);
    auto headerJson = json::parse(jsonResponse);
    const auto& standingsTable = headerJson["MRData"]["StandingsTable"];
    if (currentType == standingType::Driver) // if else blocks and ternaries that have this def, look like they default to this but the toggle changes this.
    {
        header = standingsTable["season"].get<std::string>() + " Drivers Championship - Round " + standingsTable["round"].get<std::string>();
    }
    else
    {
        header = standingsTable["season"].get<std::string>() + " Constructors Championship - Round " + standingsTable["round"].get<std::string>();
    }

    processor = std::make_unique<T>();
    const GenData results = processor->process(jsonResponse);
    return results;
}


void Pages::ShowRace(const std::string& url) const
{
    auto screen = ScreenInteractive::TerminalOutput();

    const Request request;
    std::unique_ptr<ResBuild> processor;
    std::string jsonResponse = request.createRequest(url);
    auto headerJson = json::parse(jsonResponse);
    const auto& raceResult = headerJson["MRData"]["RaceTable"]["Races"][0];
     std::string header = raceResult["season"].get<std::string>() + " " + raceResult["raceName"].get<std::string>() +
          " Results @ " + raceResult["Circuit"]["circuitName"].get<std::string>() + " - Race [" + raceResult["round"].get<std::string>() + "]";
    const raceDetails results = processor->RaceDetails(jsonResponse);

    std::vector<std::string> raceRes; // add laps and team name to this.
    for (const auto& res : results)
    {
        std::string line = res.position + ". " + res.name + " - " + res.status + " - " + res.delta +  " - " + res.points + "+pts";
        raceRes.push_back(line);
    }

    int selected = 0;
    auto RaceMenu = Menu(&raceRes, &selected);
    auto menuButton = Button("Back to Menu", [&]
    {
        screen.ExitLoopClosure()();
    }, ButtonOption::Ascii());

    const auto vertComp = Container::Vertical ({
        RaceMenu,
        menuButton,
    });

    const auto renderer = Renderer(vertComp, [&]
    {
        return vbox({
            text(header) | center,
            separator(),
            RaceMenu->Render() | center,
            separator(),
            hbox({
                menuButton->Render() | center,
            }) | center,
        }) | border | size(WIDTH, EQUAL, 150) | center;
    });
    screen.Loop(renderer);
}



void Pages::ShowMenu(){
    auto screen = ScreenInteractive::TerminalOutput();

    const std::vector<std::string> entries = {
        "Find a standing",
        "Latest Race",
        "Exit",
    };
    int selected = 0;

    MenuOption option;
    option.on_enter = [&] {
        if (selected == 0)
        {
            ShowInput(); // Takes us to second page
        }
        else if (selected == 1)
        {
            ShowRace(test);
        }
        else
        {
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

void Pages::ShowInput()
{
    auto screen = ScreenInteractive::TerminalOutput();

    std::string seasonYear;
    std::string url;
    int selected = static_cast<int>(currentType);

    Component seasonInput = Input(&seasonYear, "Enter a season...");
    Component standingCheck = Toggle(&options, &selected);
    Component backBtn = Button("Back to Menu", screen.ExitLoopClosure(), ButtonOption::Ascii());
    Component submitBtn = Button("Submit", [&] {

        currentType = static_cast<standingType>(selected);
        std::string endpoint = (currentType == standingType::Driver) ? driverBase : constBase;
        url = base + seasonYear + endpoint;
        // this calls our next function, passes built endpoint to display respective year standings. Our Standing page returns a bool if we want to go straight to menu
        if (ShowResults(url)) { screen.ExitLoopClosure()(); }
    }, ButtonOption::Ascii());

    auto buttons = Container::Horizontal({
        submitBtn,
        backBtn,
    });

    const auto vertComp = Container::Vertical({
        seasonInput,
        standingCheck,
        buttons,
    });

    const auto renderer = Renderer(vertComp, [&] {
        return vbox({
            hbox(text(" Season Year : "), seasonInput->Render()),
            separator(),
            hbox(text("Select a standing: "), standingCheck->Render()),
            separator(),
            hbox({
                submitBtn->Render(),
                backBtn->Render(),
            })
        }) | border | center;
    });

    screen.Loop(renderer);
}

bool Pages::ShowResults(const std::string &url)
{
    auto screen = ScreenInteractive::TerminalOutput();
    bool menuBack = false;
    std::string header;
    const GenData results = (currentType == standingType::Driver) ? call<DriverStandings>(url, header) : call<ConstructorStandings>(url, header);

    std::vector<std::string> standingsList;
    if (currentType == standingType::Driver) // feel like there is a better approach to this.
        {
        for (const auto& standing : results)
        {
            std::string line = standing.position + ". " + standing.name + " (" + standing.team.value() + ") - " + standing.points + " pts";
            standingsList.push_back(line);
        }
    }
    else
    {
        for (const auto& standing : results)
        {
            std::string line = standing.position + ". " + standing.name + " - " + standing.points + " pts";
            standingsList.push_back(line);
        }
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


