# step [![version](https://img.shields.io/badge/version-0.1.0-red.svg)](https://semver.org) [![Build Status](https://travis-ci.org/albin-johansson/Centurion.svg?branch=master)](https://travis-ci.org/albin-johansson/step) [![codecov](https://codecov.io/gh/albin-johansson/step/branch/master/graph/badge.svg)](https://codecov.io/gh/albin-johansson/step) [![Language grade: C/C++](https://img.shields.io/lgtm/grade/cpp/g/albin-johansson/step.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/albin-johansson/step/context:cpp) [![Language](https://img.shields.io/badge/C%2B%2B-17-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B#Standardization) ![GitHub commit activity](https://img.shields.io/github/commit-activity/m/albin-johansson/step) ![GitHub repo size](https://img.shields.io/github/repo-size/albin-johansson/step)  [![License](https://img.shields.io/badge/license-MIT-blue.svg)](https://opensource.org/licenses/MIT)

***step*** (name derived from **s**imple **t**il**e**d **p**arser), is a parsing library for the Tiled map editors JSON format that is written in modern C++17. It can be used both as a shared library or in a pseudo-"header-only" mode where you also include the source files.

This library *should* be usable on any platform that can use a reasonably recent C++ compiler that adheres to the C++17 standard. However, step is developed on Windows, primarily using GCC and MSVC, and is tested on Windows and Linux (Ubuntu). Use the library in the header-only mode if there are no binaries for your system.

Refer to the in-source documentation and official Tiled documentation for details about the various components and properties.

Happy coding! :heart:

## Usage

```C++
#include <step.h>

int main()
{
  auto map = step::parse("maps/", "my_tiled_map.json");
}
```

## Tools, API:s and dependencies

* [**nlohmann/json**](https://github.com/nlohmann/json) - An awesome modern C++ library for parsing JSON. This library is bundled in the repository.
* [**joboccara/NamedType**](https://github.com/joboccara/NamedType) - A great library for
 creating strong types to increase type safety and code clarity.
* [**doctest**](https://github.com/onqtam/doctest) - Simple and fast header-only testing
 framework that is used for the unit tests.

## See also

* [**Tiled**](https://github.com/bjorn/tiled) - The amazing tile map editor that produces the maps that step parses.
* [**Tiled documentation**](https://doc.mapeditor.org/en/stable/) - The reference used for developing the library, along with the Tiled editor itself.
