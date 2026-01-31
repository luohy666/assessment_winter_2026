#include <iostream>
#include <string>

#include "rm_a0/a0_08_raii_handle.hpp"

int main() {
  std::string in_path, out_path;
  if (!(std::cin >> in_path >> out_path))
    return 0;

  if (rm_a0::CopyFile(in_path, out_path)) {
    std::cout << "OK\n";
  } else {
    std::cout << "FAIL\n";
  }

  return 0;
}
