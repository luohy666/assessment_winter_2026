#pragma once

#include <string>

namespace rm_a0 {

struct ScoreStatsResult {
  std::string top_name;
  int top_score = 0;
  double avg = 0.0;
};

// Parses the full input for A0-05.
// If parsing fails, ok=false and result is unspecified.
ScoreStatsResult ComputeScoreStats(const std::string &input, bool &ok);

// Returns:
//   top=<name> <score>\n
//   avg=<avg>\n   (avg with 2 decimals)
// If parsing fails, ok=false and returns empty string.
std::string SolveScoreStats(const std::string &input, bool &ok);

} // namespace rm_a0
