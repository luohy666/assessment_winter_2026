#pragma once

#include <string>

namespace rm_a0 {

bool IsLeapYear(int year);

std::string FormatLeapYearAnswer(bool is_leap_year);

// Parses year from input, returns "YES\n" or "NO\n".
// If parsing fails, ok=false and returns empty string.
std::string SolveLeapYear(const std::string &input, bool &ok);

} // namespace rm_a0
