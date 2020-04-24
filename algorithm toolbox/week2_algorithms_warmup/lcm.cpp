#include <iostream>
#include <cassert>
#include <algorithm>

long long lcm_naive(int a, int b) {
  for (long l = 1; l <= (long long) a * b; ++l)
    if (l % a == 0 && l % b == 0)
      return l;

  return (long long) a * b;
}

int gcd_euclid(int x, int y){
  if(x < 0 || y < 0) return 1;
  int b = std::min(x,y);
  int a = std::max(x,y);

  if(b == 0) return std::max(1,a);
  else return gcd_euclid(b, a%b);
}

long long lcm_euclid(int x, int y){
	return ((long long)x * y) / gcd_euclid(x,y);
}

void test_solution(){
  assert(lcm_euclid(12,18) == 36);
  assert(lcm_euclid(40,25) == 200);
  for(int n=1; n<20; n++)
    for(int m=n+125; m<n+150; m++)
    assert(lcm_euclid(n, m) == lcm_naive(m, n));
}

int main() {
  int a, b;
  std::cin >> a >> b;
  // std::cout << lcm_naive(a, b) << std::endl;
  // test_solution();
  std::cout << lcm_euclid(a, b) << std::endl;
  return 0;
}
