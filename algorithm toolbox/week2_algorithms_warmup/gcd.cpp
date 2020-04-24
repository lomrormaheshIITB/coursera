#include <iostream>
#include <cassert>
#include <algorithm>

int gcd_naive(int a, int b) {
  int current_gcd = 1;
  for (int d = 2; d <= a && d <= b; d++) {
    if (a % d == 0 && b % d == 0) {
      if (d > current_gcd) {
        current_gcd = d;
      }
    }
  }
  return current_gcd;
}

int gcd_euclid(int x, int y){
  if(x < 0 || y < 0) return 1;
  int b = std::min(x,y);
  int a = std::max(x,y);

  if(b == 0) return std::max(1,a);
  else return gcd_euclid(b, a%b);
}

void test_solution(){
  assert(gcd_euclid(12,18) == 6);
  assert(gcd_euclid(40,25) == 5);
  for(int n=1; n<20; n++)
    for(int m=n; m<n+50; m++)
    assert(gcd_euclid(n, m) == gcd_naive(m, n));
}

int main() {
  int a, b;
  std::cin >> a >> b;
  // std::cout << gcd_naive(a, b) << std::endl;
  // test_solution();
  std::cout << gcd_euclid(a, b) << std::endl;
  return 0;
}
