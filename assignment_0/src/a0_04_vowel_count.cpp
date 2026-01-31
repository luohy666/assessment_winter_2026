#include <cctype>
#include <iostream>
#include <string>

#include "rm_a0/a0_04_vowel_count.hpp"

int main() {
  std::string line;
  if (!std::getline(std::cin, line)) {
    return 0;
  }

  std::cout << rm_a0::CountVowels(line) << "\n";

  return 0;
}
