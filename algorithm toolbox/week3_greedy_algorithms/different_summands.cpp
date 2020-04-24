#include <iostream>
#include <vector>
#include <cmath>

using std::vector;

vector<int> optimal_summands(int n) {
  vector<int> summands;
  //write your code here
  if(n < 1) return summands;
  if(n == 2) { summands.push_back(2); return summands;}
  
  int p = sqrt(2*n);
  int num = -1;

  for(int i=p; i>0; i--){
    int temp = (i*i + i) / 2;
    if(n/temp == 1){
      num = i;
      // std::cout << "p= " << i << "\n";
      break;
    }

  }

  for(int i=1; i<num; i++)
    summands.push_back(i);
  summands.push_back(n-(num*num - num)/2);
   
  return summands;
}

int main() {
  int n;
  std::cin >> n;
  vector<int> summands = optimal_summands(n);
  std::cout << summands.size() << '\n';
  for (size_t i = 0; i < summands.size(); ++i) {
    std::cout << summands[i] << ' ';
  }
}
