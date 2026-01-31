#pragma once

#include <string>

namespace rm_a0 {

double CelsiusToFahrenheit(double celsius);

std::string FormatFahrenheit(double fahrenheit);

// Parses Celsius from input, returns formatted Fahrenheit with 2 decimals +
// '\n'. If parsing fails, ok=false and returns empty string.
std::string SolveTemperature(const std::string &input, bool &ok);

} // namespace rm_a0
