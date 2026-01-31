#include <iostream>
#include <sstream>
#include <string>

#include "rm_a0/a0_07_log_analyzer.hpp"

int main() {
  std::string path;
  if (!std::getline(std::cin, path)) {
    return 0;
  }

  bool ok = false;
  std::string out = rm_a0::SolveLogAnalyzer(path + "\n", ok);
  std::cout << out;

  return 0;
}
