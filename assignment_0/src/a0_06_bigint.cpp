#include <iostream>
#include <sstream>

#include "rm_a0/a0_06_bigint.hpp"

int main() {
  std::ostringstream oss;
  oss << std::cin.rdbuf();

  bool ok = false;
  std::string out = rm_a0::SolveBigIntAdd(oss.str(), ok);
  if (!ok) {
    return 0;
  }

  std::cout << out;
  return 0;
}
