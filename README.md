# F1 Championship Tracker

A C++ terminal application for viewing Formula 1 championship standings and race results using real-time data from the Jolpica-F1 API.

## Overview

This interactive terminal application provides:
- **Driver and Constructor Standings**: View championship standings for any F1 season
- **Race Results**: Display detailed results from specific races including the latest race
- **Driver Details**: Access detailed driver information including statistics and biography
- **Interactive TUI**: Terminal user interface built with FTXUI
- **Accurate Data**: Powered by the Jolpica-F1 API for up-to-date F1 information

## Prerequisites

- **C++ Compiler**: Supporting C++20 standard (GCC 10+, Clang 10+, MSVC 2019+)
- **CMake**: Version 3.31 or higher
- **vcpkg**: Package manager for C++ dependencies

### Required Dependencies (Auto-installed via vcpkg)
- **nlohmann/json**: JSON parsing and manipulation
- **libcurl**: HTTP requests to F1 API
- **FTXUI**: Terminal user interface components

## Installation & Setup

### 1. Clone the Repository
```bash
git clone <your-repo-url>
cd F1-Championship-Tracker
```

### 3. Install Dependencies
Run the appropriate command for your platform from the project root:

```bash
# Linux
vcpkg install nlohmann-json curl ftxui --triplet x64-linux

# Windows
vcpkg install nlohmann-json curl ftxui --triplet x64-windows

# macOS
vcpkg install nlohmann-json curl ftxui --triplet x64-osx
```

### 4. Build the Project

#### Using CMake Command Line
```bash
mkdir build
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=/path/to/vcpkg/scripts/buildsystems/vcpkg.cmake
make # Linux/macOS
# cmake --build . # Windows
```

#### Using CLion
1. Open the project folder in CLion
2. Go to File → Settings → Build, Execution, Deployment → CMake
3. Add CMake option: `-DCMAKE_TOOLCHAIN_FILE=/path/to/vcpkg/scripts/buildsystems/vcpkg.cmake`
4. Build using Ctrl+F9 (Windows/Linux) or Cmd+F9 (Mac)

#### Using Visual Studio (Windows)
1. Open the folder in Visual Studio
2. Configure CMake settings to point to vcpkg toolchain
3. Build using Ctrl+Shift+B

### 5. Run the Application
```bash
# From build directory
./F1          # Linux/macOS
.\F1.exe      # Windows

# From CLion cmake-build-debug
./cmake-build-debug/F1
```

## Usage Guide

### Main Menu Navigation
Upon starting the application, you'll see three options:

1. **"Find a standing"**: View championship standings for any season
2. **"Latest Race"**: View results from the most recent F1 race
3. **"Exit"**: Close the application

### Viewing Championship Standings
1. Select "Find a standing"
2. Enter a season year (e.g., 2023, 2024)
3. Choose between "Driver" or "Constructor" standings
4. Browse the results and select any driver for detailed information

### Viewing Race Results
1. Select "Latest Race" from the main menu
2. View detailed race results including positions, status, and points
3. Use "Back to Menu" to return to the main screen

### Driver Details
- From any standings view, select a driver to see:
  - Driver number
  - Date of birth
  - Nationality
  - Wikipedia link

## Troubleshooting

### Common Build Issues

#### CMake can't find vcpkg
- **Problem**: CMake doesn't recognize vcpkg dependencies
- **Solution**: Ensure you're using the correct toolchain file path:
```bash
cmake .. -DCMAKE_TOOLCHAIN_FILE=/full/path/to/vcpkg/scripts/buildsystems/vcpkg.cmake
```

#### Missing dependencies
- **Problem**: Libraries not found during build
- **Solution**: Reinstall dependencies and ensure correct triplet:
```bash
vcpkg remove nlohmann-json curl ftxui
vcpkg install nlohmann-json curl ftxui --triplet x64-linux # adjust for your OS
```

#### CMake version too old
- **Problem**: CMake version requirements not met
- **Solution**: Either upgrade CMake or modify CMakeLists.txt:
```cmake
cmake_minimum_required(VERSION 3.20)  # Lower version
```

### Runtime Issues

#### Invalid season data
- **Problem**: No data returned for entered season
- **Solution**: Use valid F1 seasons (1950-present)
- **Note**: Future seasons may not have complete data

#### UI display issues
- **Problem**: Terminal UI not rendering correctly
- **Solution**: Ensure terminal supports ANSI colors and UTF-8
- **Windows**: Use Windows Terminal or enable ANSI support

## Notes

### Architecture Overview
- **Pages.cpp**: Handles all UI screens and user interaction
- **Request.cpp**: Manages HTTP requests using libcurl
- **Response.cpp**: Processes JSON responses and extracts F1 data
- **standings.h**: Defines data structures for F1 entities

### Key Design Patterns
- **Template Method**: Used in `Pages::call<T>()` for processing different standing types
- **Strategy Pattern**: Different response processors for drivers vs constructors
- **RAII**: Automatic cleanup of curl resources

## Performance Notes

- API calls are synchronous and may take 1-3 seconds
- JSON parsing is optimized for the expected API response structure
- Terminal UI is lightweight and responsive
- No local caching - all data is fetched in real-time

## Credits

- **Jolpica-F1 API**: https://github.com/jolpica/jolpica-f1
- **FTXUI**: https://github.com/ArthurSonzogni/FTXUI
- **nlohmann/json**: https://github.com/nlohmann/json
- **libcurl**: https://curl.se/

---

**Note**: This application requires an active internet connection to fetch real-time F1 data. Historical data availability depends on the Jolpica-F1 API coverage.
