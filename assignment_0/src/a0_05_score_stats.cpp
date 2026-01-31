#include <iostream>
#include <sstream>
#include <string>

#include "rm_a0/a0_05_score_stats.hpp"

int main() {
  std::ostringstream oss;
  oss << std::cin.rdbuf();

  bool ok = false;
  std::string out = rm_a0::SolveScoreStats(oss.str(), ok);
  if (!ok) {
    return 0;
  }

  std::cout << out;

  return 0;
}
