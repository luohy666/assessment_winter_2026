#include <iostream>

#include "rm_a0/a0_01_temperature.hpp"

int main() {
  double celsius = 0.0;
  if (!(std::cin >> celsius)) {
    return 0;
  }
  std::cout << rm_a0::FormatFahrenheit(rm_a0::CelsiusToFahrenheit(celsius));
  return 0;
}
