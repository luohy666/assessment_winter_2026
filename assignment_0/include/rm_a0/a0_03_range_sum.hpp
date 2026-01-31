#pragma once

#include <string>

namespace rm_a0 {

long long RangeSum(long long l, long long r);

// Parses "l r" from input, returns sum + "\n".
// If parsing fails, ok=false and returns empty string.
std::string SolveRangeSum(const std::string &input, bool &ok);

} // namespace rm_a0
