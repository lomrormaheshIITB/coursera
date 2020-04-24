#include <iostream>
#include <vector>
#include <algorithm>
#include<bits/stdc++.h>
using namespace std;

using std::vector;

bool sortinrev(const pair<double,int> &a, const pair<double,int> &b) 
{ 
       return (a.first > b.first); 
}

double get_optimal_value(int capacity, vector<int> weights, vector<int> values) {
  double value = 0.0;
  double fill = (double)capacity;

  // write your code here
  // vect = value_per_weigth
  vector< pair<double, int> > vect;
  for(int i=0; i<weights.size(); i++){
    vect.push_back(make_pair((double)values[i] / weights[i], weights[i]));
  }

  sort(vect.begin(), vect.end(), sortinrev);

  for (int i = 0; i < weights.size(); ++i)
  {
    /* code */
    // std::cout << "(" << vect[i].first << "," << vect[i].second << ")" << ", ";
    if(fill > 0){
      double a = std::min(fill, (double)vect[i].second);
      value = value + a*vect[i].first;
      fill = fill - a;
    }
  }

  // std::cout << std::endl;
  return value;
}

int main() {
  int n;
  int capacity;
  std::cin >> n >> capacity;
  vector<int> values(n);
  vector<int> weights(n);
  for (int i = 0; i < n; i++) {
    std::cin >> values[i] >> weights[i];
  }

  double optimal_value = get_optimal_value(capacity, weights, values);

  std::cout.precision(10);
  std::cout << optimal_value << std::endl;
  return 0;
}
