#pragma once

#include <cstddef>
#include <string>

namespace rm_a0 {

std::size_t CountVowels(const std::string &line);

// Takes first line as input (may contain spaces), returns count + "\n".
// If input is empty (no line), ok=false and returns empty string.
std::string SolveVowelCount(const std::string &input, bool &ok);

} // namespace rm_a0
