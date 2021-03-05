#ifndef STEP_API_HEADER
#define STEP_API_HEADER

// Define STEP_API for any platform
// https://atomheartother.github.io/c++/2018/07/12/CPPDynLib.html
#if defined(_WIN32) && !defined(STEP_API)
#ifdef WIN_EXPORT
#define STEP_API __declspec(dllexport)
#else
#define STEP_API __declspec(dllimport)
#endif  // WIN_EXPORT
#else
#define STEP_API
#endif  // defined(_WIN32) && !defined(STEP_API)

// Used for getters that aren't inlined
#define STEP_QUERY [[nodiscard]] STEP_API

#endif  // STEP_API_HEADER