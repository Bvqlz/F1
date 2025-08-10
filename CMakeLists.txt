cmake_minimum_required(VERSION 3.31)
project(F1)

set(CMAKE_CXX_STANDARD 20)

add_executable(F1 main.cpp
        src/Response.cpp
        src/Request.cpp
)

find_package(nlohmann_json CONFIG REQUIRED)
target_link_libraries(F1 PRIVATE nlohmann_json::nlohmann_json)

find_package(curl CONFIG REQUIRED)
target_link_libraries(F1 PRIVATE CURL::libcurl)

find_package(ftxui REQUIRED)
target_link_libraries(F1
        PRIVATE ftxui::screen
        PRIVATE ftxui::dom
        PRIVATE ftxui::component
)