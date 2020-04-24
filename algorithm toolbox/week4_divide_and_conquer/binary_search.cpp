#include <iostream>
#include <cassert>
#include <vector>
#include <stdio.h> 
#include <stdlib.h>
#include <algorithm>

using std::vector;

int binary_helper(const vector<int> &a, int low, int high, int x){
  // std::cout <<"----- ENTER ---------\n";
	// std::cout <<"\n" << low << " " <<high << " " <<  x << "\n";

  if(high < low) return -1;

  
  int mid = (low + high)/2;
  if(a[mid] == x) return mid;
  else if(a[low] == x) return low;
  else if(a[high] == x) return high;
  else if(a[mid] < x) return binary_helper(a, mid+1, high, x);
  else return binary_helper(a, low, mid-1, x);

}



int binary_search(const vector<int> &a, int x) {
  // high is included
  int low = 0, high = (int)a.size() - 1; 

  //write your code here
  int mid = (high + low)/2;

  if(a[mid] == x) return mid;
  else if(a[high] == x) return high;
  else if(a[low] == x) return low;
  else if(a[high] < x) return -1;
  else if(a[low] > x) return -1;
  else if(a[mid] < x) return binary_helper(a, mid+1, high, x);
  else return binary_helper(a, low, mid-1, x);
}




int linear_search(const vector<int> &a, int x) {
  for (size_t i = 0; i < a.size(); ++i) {
    if (a[i] == x) return i;
  }
  return -1;
}



int main() {
  int n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < a.size(); i++) {
    std::cin >> a[i];
  }
  sort(a.begin(), a.end());
  int m;
  std::cin >> m;
  vector<int> b(m);
  for (int i = 0; i < m; ++i) {
    std::cin >> b[i];
  }

  for (int i = 0; i < m; ++i) {
    //replace with the call to binary_search when implemented
    // std::cout << linear_search(a, b[i]) << ' ';
    std::cout << binary_search(a, b[i]) << ' ';
    }
}
