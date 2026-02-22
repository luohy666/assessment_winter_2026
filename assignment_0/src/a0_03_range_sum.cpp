#include <iostream>

int main(){
  long long l = 0, r = 0;
  if(std::cin >> l >> r){
    if (l > r){
      long long temp = l;
      l = r;
      r = temp;
    }
    long long sum = (r * (r + 1) / 2 - (l - 1) * l / 2);
    std::cout << sum << std::endl;
  } 

  return 0;
}