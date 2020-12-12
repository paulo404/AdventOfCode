#include <iostream>
#include <set>

std::set<int> s;

void solution1() {
  for ( const auto& v : s ) {
    if ( const auto& r = s.find(2020-v); r != s.end() ) {
      std::cout << v * *r << std::endl;
      return;
    }
  }
}

void solution2() {
  for ( const auto& x : s ) {
    for ( const auto& y : s ) {
      //check if valid value for y
      int sum = x + y;
      if ( sum > 2020 ) break;

      if ( const auto& z = s.find(2020-sum); z != s.end() ) {
        std::cout << x * y * *z << std::endl;
        return;
      }
    }
  }
}

int main() {
  int x;
  while ( std::cin >> x ) s.emplace(x);

  //solution1();
  solution2();

  return 0;
}
