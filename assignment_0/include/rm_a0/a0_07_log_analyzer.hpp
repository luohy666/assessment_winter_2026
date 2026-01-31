#pragma once

#include <string>

namespace rm_a0 {

struct LogStats {
  long long info = 0;
  long long warn = 0;
  long long error = 0;
  double avg_ms = 0.0;
  std::string max_level;
  long long max_ms = 0;
};

// Reads and analyzes the file at path.
// On failure (cannot open or no valid lines), ok=false and result unspecified.
LogStats AnalyzeLogFile(const std::string &path, bool &ok);

// Input: a single line path.
// Output:
//   INFO=<cnt>\nWARN=<cnt>\nERROR=<cnt>\navg=<avg>\nmax=<level> <ms>\n
// If file can't be opened / input invalid: ok=false and returns "FAIL\n".
std::string SolveLogAnalyzer(const std::string &input, bool &ok);

} // namespace rm_a0
