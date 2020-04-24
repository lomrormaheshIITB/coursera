#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>  // std::ceil

using std::vector;
using std::cin;
using std::cout;
using std::swap;
using std::pair;
using std::make_pair;

void print_vector(vector<int> &v){
  for(auto it=v.begin(); it != v.end(); it++)
    std::cout<<*it << " ";
  std::cout << "\n";
  return;
}

class HeapBuilder {
 private:
  vector<int> data_;
  vector< pair<int, int> > swaps_;

  void WriteResponse() const {
    cout << swaps_.size() << "\n";
    for (int i = 0; i < swaps_.size(); ++i) {
      cout << swaps_[i].first << " " << swaps_[i].second << "\n";
    }
  }

  void ReadData() {
    int n;
    cin >> n;
    data_.resize(n);
    for(int i = 0; i < n; ++i)
      cin >> data_[i];
  }

  void GenerateSwaps() {
    swaps_.clear();
    // The following naive implementation just sorts 
    // the given sequence using selection sort algorithm
    // and saves the resulting sequence of swaps.
    // This turns the given array into a heap, 
    // but in the worst case gives a quadratic number of swaps.
    //
    // TODO: replace by a more efficient implementation
    // for (int i = 0; i < data_.size(); ++i)
    //   for (int j = i + 1; j < data_.size(); ++j) {
    //     if (data_[i] > data_[j]) {
    //       swap(data_[i], data_[j]);
    //       swaps_.push_back(make_pair(i, j));
    //     }
    //   }

   
    for(int i=ceil(data_.size()/2); i>=0; i--){
      int min_index = i;
      while(true){
        int temp = min_index;
        int l = 2*min_index+1;
        int r = 2*min_index+2;

        if(l < data_.size()  and data_[l] < data_[min_index])
          min_index = l;
        if(r < data_.size()  and data_[r] < data_[min_index])
          min_index = r;

        if(min_index != temp  ){
          swap(data_[temp], data_[min_index]);
          swaps_.push_back(make_pair(temp, min_index));
        }
        else break;
      }
    }

  }

 public:
  void Solve() {
    ReadData();
    GenerateSwaps();
    WriteResponse();
  }
};



int main() {
  std::ios_base::sync_with_stdio(false);
  HeapBuilder heap_builder;
  heap_builder.Solve();
  return 0;
}
