#include "rm_a0/a0_lib.hpp"

#include <iostream>
#include <sstream>
#include <string>

int main() {
  std::ostringstream oss;
  oss << std::cin.rdbuf();

  bool ok = false;
  std::string out = rm_a0::RunCommandDispatcher(oss.str(), ok);
  if (!ok) {
    std::cout << "FAIL\n";
    return 0;
  }

  std::cout << out;
  return 0;
}
