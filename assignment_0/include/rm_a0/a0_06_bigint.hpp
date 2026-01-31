#pragma once

#include <iosfwd>
#include <string>
#include <vector>

namespace rm_a0 {

class BigInt {
public:
  BigInt();

  // Constructs from a non-negative decimal string.
  explicit BigInt(const std::string &s);

  friend BigInt operator+(const BigInt &a, const BigInt &b);
  friend std::ostream &operator<<(std::ostream &os, const BigInt &x);

private:
  // Little-endian digits, each 0..9.
  std::vector<int> digits_;
};

// Reads two lines A and B, returns (A+B)+"\n".
// If parsing fails, ok=false and returns empty string.
std::string SolveBigIntAdd(const std::string &input, bool &ok);

} // namespace rm_a0
