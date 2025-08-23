
-----

## F1 Championship Tracker

A **C++ terminal application** for viewing Formula 1 championship standings and race results using the **Ergast F1 API**.

### Features

  * View driver and constructor standings for any F1 season.
  * Display detailed results for specific races.
  * Interactive terminal-based user interface (TUI) built with **FTXUI**.
  * Real-time data powered by the **Ergast F1 API**.

-----

### Prerequisites

Before you begin, make sure you have the following installed:

  * A **C++20** compatible compiler (like GCC, Clang, or MSVC).
  * **CMake** version **3.31** or higher.
  * **vcpkg** for managing dependencies.

-----

### Dependencies

This project uses the following libraries, which will be installed via `vcpkg`:

  * [`nlohmann/json`](https://www.google.com/search?q=%5Bhttps://github.com/nlohmann/json%5D\(https://github.com/nlohmann/json\)) - For JSON parsing.
  * [`curl`](https://www.google.com/search?q=%5Bhttps://curl.se/%5D\(https://curl.se/\)) - For making HTTP requests to the API.
  * [`ftxui`](https://www.google.com/search?q=%5Bhttps://github.com/ArthurSonzogni/FTXUI%5D\(https://github.com/ArthurSonzogni/FTXUI\)) - For the terminal UI.

-----

### Getting Started

#### Clone the Repository

Start by cloning the project to your local machine:

```
git clone <your-repo-url>
cd F1-Championship-Tracker
```

#### Install Dependencies

Use `vcpkg` to install the required libraries. Run the appropriate command for your operating system from the project's root directory:

```
# For Linux
vcpkg install nlohmann-json curl ftxui --triplet x64-linux

# For Windows
vcpkg install nlohmann-json curl ftxui --triplet x64-windows

# For macOS
vcpkg install nlohmann-json curl ftxui --triplet x64-osx
```

#### Build the Project

Create a build directory and use CMake to configure and build the project.

```bash
mkdir build
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=/path/to/vcpkg/scripts/buildsystems/vcpkg.cmake
make # On Windows, use: cmake --build .
```

-----

### Usage

#### Run the Application

From the `build` directory, you can run the application:

```bash
# On Linux / macOS
./F1

# On Windows
.\F1.exe
```

#### Navigation

Once the application is running, use the interactive menu to navigate:

  * **"Find a standing"**: View championship standings for any season.
  * **"Latest Race"**: View results from the most recent race.
  * **"Exit"**: Close the application.

### API Credits

This application uses the [**Ergast F1 API**](http://ergast.com/mrd/) for all Formula 1 data.



