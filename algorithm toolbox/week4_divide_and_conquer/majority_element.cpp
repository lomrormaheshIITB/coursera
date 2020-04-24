#include <algorithm>
#include <iostream>
#include <vector>

using std::vector;

int get_majority_element(vector<int> &a, int left, int right) {
  if (left == right) return -1;
  if (left + 1 == right) return a[left];
  //write your code here
  // n = max_element

  int current_count = 0;
  int current_element = -1;
  for(int i=0; i<right; i++){
    if(a[i] == current_element) {
      current_count++;
      if(current_count > right/2) return 1;
    }
    else {
      current_element = a[i];
      current_count = 1;
    }
  }

  return -1;
}

int main() {
  int n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < a.size(); ++i) {
    std::cin >> a[i];
  }
  sort(a.begin(), a.end());
  std::cout << (get_majority_element(a, 0, a.size()) != -1) << '\n';
}
