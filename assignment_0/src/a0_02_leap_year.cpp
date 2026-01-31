#include <iostream>

#include "rm_a0/a0_02_leap_year.hpp"

int main() {
  int year = 0;
  if (!(std::cin >> year)) {
    return 0;
  }

  std::cout << rm_a0::FormatLeapYearAnswer(rm_a0::IsLeapYear(year));

  return 0;
}
