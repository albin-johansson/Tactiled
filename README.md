# step [![version](https://img.shields.io/badge/version-0.2.0-blue.svg)](https://semver.org) [![Build Status](https://travis-ci.org/albin-johansson/Centurion.svg?branch=master)](https://travis-ci.org/albin-johansson/step) [![Build status](https://ci.appveyor.com/api/projects/status/0ijia28k5u95ro1r?svg=true)](https://ci.appveyor.com/project/AlbinJohansson/step) [![codecov](https://codecov.io/gh/albin-johansson/step/branch/master/graph/badge.svg)](https://codecov.io/gh/albin-johansson/step) [![Language grade: C/C++](https://img.shields.io/lgtm/grade/cpp/g/albin-johansson/step.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/albin-johansson/step/context:cpp) [![Language](https://img.shields.io/badge/C%2B%2B-17-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B#Standardization) ![GitHub repo size](https://img.shields.io/github/repo-size/albin-johansson/step)  [![License](https://img.shields.io/badge/license-MIT-blue.svg)](https://opensource.org/licenses/MIT)

***step*** (name derived from **s**imple **t**il**e**d **p**arser), is a parsing library for the Tiled map editors JSON format that is written in modern C++17.

Refer to the in-source documentation and official Tiled documentation for details about the various components and properties.

Happy coding! :heart:

## Usage

```C++
#include <memory>

#include <step_map.hpp>

int main()
{
  auto map = std::make_unique<step::map>("maps/my_tiled_map.json");
  return 0;
}
```

## Dependencies

* [**nlohmann/json**](https://github.com/nlohmann/json) - An awesome modern C++ library for parsing JSON. This library is bundled in the repository.
* [**joboccara/NamedType**](https://github.com/joboccara/NamedType) - A great library for
 creating strong types to increase type safety and code clarity.

## See also

* [**Tiled**](https://github.com/bjorn/tiled) - The tile map editor that produces the maps that step parses.
* [**Tiled documentation**](https://doc.mapeditor.org/en/stable/) - The reference used for developing the library, along with the Tiled editor itself.
