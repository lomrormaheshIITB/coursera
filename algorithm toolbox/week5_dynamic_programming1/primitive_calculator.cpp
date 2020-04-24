#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
using namespace std;

using std::vector;

vector<int> optimal_sequence(int n) {
  std::vector<int> sequence;
  while (n >= 1) {
    sequence.push_back(n);
    if (n % 3 == 0) {
      n /= 3;
    } else if (n % 2 == 0) {
      n /= 2;
    } else {
      n = n - 1;
    }
  }
  reverse(sequence.begin(), sequence.end());
  return sequence;
}

bool even(int n){
  return n % 2 == 0;
}

bool teven(int n){
  return n % 3 == 0;
}

vector<int> my_optimal_answer(int n){
  // +1, x2, x3  1<= n <= 10^6
  // assert(1 <= n and n <= 1000000);
  if( 1 > n or n > 1000000) exit(1);
  std::vector<int> sequence;
  //Base Cases
  if(n <= 3){
    sequence.push_back(1);
    if( n == 2) sequence.push_back(2);
    if( n == 3) sequence.push_back(3);
    return sequence;
  }

  int previous[n+1];
  int steps[n+1];
  previous[0] = -1;
  previous[1] = 0;
  previous[2] = 1;
  previous[3] = 1;
  steps[0] = 0;
  steps[1] = 0;
  steps[2] = 1;
  steps[3] = 1;

  // std::cout<<" ------ ENter ------\n";
  int i=4;
  while(i <= n){
    bool two = even(i);
    bool three = teven(i);

    if(two and three){
      steps[i] = min(steps[i/3], min(steps[i/2], steps[i-1])) + 1;
      if(steps[i] == steps[i/3] + 1) previous[i] = i / 3;
      else if(steps[i] == steps[i/2] + 1) previous[i] = i / 2;
      else if(steps[i] == steps[i-1] + 1) previous[i] = i - 1;
    }
    else if(three){
      steps[i] = min(steps[i/3], steps[i-1]) + 1;
      if(steps[i] == steps[i/3] + 1) previous[i] = i / 3;
      else if(steps[i] == steps[i-1] + 1) previous[i] = i - 1;
    }
    else if(two){
      steps[i] = min(steps[i/2], steps[i-1]) + 1;
      if(steps[i] == steps[i/2] + 1) previous[i] = i / 2;
      else if(steps[i] == steps[i-1] + 1) previous[i] = i - 1;
    }
    else{
      steps[i] = steps[i-1] + 1;
      previous[i] = i-1;
    }
    i++;
  }

  i--;
  // fill sequence with evaluated terms
  while(previous[i] != -1){
    sequence.push_back(i);
    i = previous[i];
  }

  reverse(sequence.begin(), sequence.end());
  return sequence;
}

int main() {
  int n;
  std::cin >> n;
  // vector<int> sequence = optimal_sequence(n);
  // std::cout << sequence.size() - 1 << std::endl;
  // for (size_t i = 0; i < sequence.size(); ++i) {
  //   std::cout << sequence[i] << " ";
  // }
  // std::cout<<"\n My_Optimal_Solution\n";
  vector<int> sequence = my_optimal_answer(n);
  std::cout << sequence.size() - 1 << std::endl;
  for (size_t i = 0; i < sequence.size(); ++i) {
    std::cout << sequence[i] << " ";
  }
  std::cout<<"\n";
}
