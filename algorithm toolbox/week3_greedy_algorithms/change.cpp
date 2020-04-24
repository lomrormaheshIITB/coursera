#include <iostream>

int get_change(int m) {
  //write your code here
	// std::cout << "---------------------\n";
	int ten = m / 10;
	int five = (m - 10*ten) / 5;
	int one  = (m - 10*ten - 5*five);

  return ten + five + one;
}

int main() {
  int m;
  std::cin >> m;
  std::cout << get_change(m) << '\n';
}
