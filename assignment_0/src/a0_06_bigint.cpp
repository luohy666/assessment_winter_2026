#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class BigInt{
  private:
  std::vector<int> digits;
  bool is_zero() const{
    return digits.empty() || (digits.size() == 1 && digits[0] == 0);
  }

  public:
  BigInt(const std::string& s = "0"){
    digits.clear();
    bool leading_zero = true;
    for(int i = s.size() - 1; i >= 0; --i){
      if(leading_zero && s[i] == '0') continue;
      leading_zero = false;
      digits.push_back(s[i] - '0');
    }
    if(digits.empty())digits.push_back(0);
  }

  BigInt(const char* s) : BigInt(std::string(s)){}

  BigInt operator+(const BigInt& other)const{
    BigInt result;
    result.digits.clear();

    int carry = 0;
    size_t max_size = std::max(digits.size(),other.digits.size());

    for(size_t i = 0; i < max_size || carry; ++i){
      int sum = carry;
      if(i < digits.size()) sum += digits[i];
      if(i < other.digits.size()) sum += other.digits[i];

      result.digits.push_back(sum % 10);
      carry = sum / 10;
    }

    return result;
  }

  friend std::ostream& operator<<(std::ostream& os, const BigInt& num){
    if(num.is_zero()){
      os<<0;
      return os;
    }
    for(int i = num.digits.size() - 1; i >= 0; --i){
      os << num.digits[i];
    }
    return os;
  }

};


int main() {
    std::string a, b;
    std::getline(std::cin, a);
    std::getline(std::cin, b);

    BigInt num1(a);
    BigInt num2(b);

    BigInt sum = num1 + num2;
    std::cout << sum << std::endl;

    return 0;
}