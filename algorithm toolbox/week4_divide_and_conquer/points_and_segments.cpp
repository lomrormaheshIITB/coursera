#include <iostream>
#include <algorithm>
#include <cassert>
#include <vector>

#include <chrono>
using namespace std::chrono;

using std::vector;

vector<int> fast_count_segments(vector<int> starts, vector<int> ends, vector<int> points) {
  vector<int> cnt(points.size());
  //write your code here

  long low = starts[0];
  long high = ends[0];

  for(size_t i=0; i<starts.size(); i++){
    if(starts[i] < low) low = starts[i];
    if(ends[i] > high) high = ends[i];
  }

  // make an array/vector (strength represent count of that point) of size (high - low + 1)
  long sz = high-low+1;
  vector<int> strength(sz);
  for(size_t i=0; i<sz; i++){
    strength[i] = 0;
  }

  // std::cout<< "low = " <<low<< " high = "<<high<<std::endl;
  for(size_t i=0; i<starts.size(); i++){
    // std::cout<<"===================\n";
    // std::cout << starts[i] << " "<<ends[i]<<std::endl;
    for(long j=starts[i]; j<=ends[i]; j++){
      // std::cout<<"------------\n";
      strength[j-low] += 1;
    }
  }

  // for(int i=0; i<sz; i++)
  //   std::cout<< strength[i] << ' ';

  // std::cout<<std::endl;
  for (size_t i = 0; i < points.size(); i++){
    if(points[i] < low) cnt[i] = 0;
    else if(points[i] > high) cnt[i] = 0;
    else cnt[i] = strength[points[i]-low];
  }

  return cnt;
}

vector<int> naive_count_segments(vector<int> starts, vector<int> ends, vector<int> points) {
  // O(n*m)
  vector<int> cnt(points.size());
  for (size_t i = 0; i < points.size(); i++) {
    for (size_t j = 0; j < starts.size(); j++) {
      cnt[i] += starts[j] <= points[i] && points[i] <= ends[j];
    }
  }
  return cnt;
}




void test_solution(){
  int s = rand();
  s = s % 100000 + 7;
  int p = rand();
  p = p % 100000 + 7;

  std::cout<<"s = "<<s<<" p = "<<p<<std::endl;

  vector<int> starts(s), ends(s);
  for (size_t i = 0; i < s; i++) {
    starts[i] = rand() % 1000 - 723;
    ends[i] = rand() % 1000 + starts[i];
  }

  vector<int> points(p);
  for (size_t i = 0; i < p; i++) {
    points[i] = rand() % 10 - 5;
  }

  auto start = high_resolution_clock::now();
  vector<int> cnt = naive_count_segments(starts, ends, points);
  auto stop = high_resolution_clock::now();

  auto start1 = high_resolution_clock::now();
  vector<int> cnt1 = fast_count_segments(starts, ends, points);
  auto stop1 = high_resolution_clock::now();

  auto duration = duration_cast<microseconds>(stop - start);
  auto duration1 = duration_cast<microseconds>(stop1 - start1);

  std::cout<<"naive time = " << duration.count() << std::endl;
  std::cout<<"fast time = " << duration1.count() << std::endl;

  std::cout<< duration.count() / duration1.count() << std::endl;

  for(int i=0; i<p; i++){
    assert(cnt[i] == cnt1[i]);
  }
  return;
}




int main() {
  // std::cout<<"testing stress test\n";
  // test_solution();
  // std::cout<<"passed stress test\n";

  int n, m;
  std::cin >> n >> m;
  vector<int> starts(n), ends(n);
  for (size_t i = 0; i < starts.size(); i++) {
    std::cin >> starts[i] >> ends[i];
  }
  vector<int> points(m);
  for (size_t i = 0; i < points.size(); i++) {
    std::cin >> points[i];
  }
  //use fast_count_segments
  // vector<int> cnt = naive_count_segments(starts, ends, points);
  vector<int> cnt1 = fast_count_segments(starts, ends, points);
  // std::cout<< "naive answer\n";
  // for (size_t i = 0; i < cnt.size(); i++) {
  //   std::cout << cnt[i] << ' ';
  // }
  // std::cout << std::endl;
  // std::cout<< "fast answer\n";
  for (size_t i = 0; i < cnt1.size(); i++) {
    std::cout << cnt1[i] << ' ';
  }
}
