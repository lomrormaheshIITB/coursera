#include <algorithm>
#include <iostream>
#include <climits>
#include <vector>

using std::vector;

struct Segment {
  int start, end;
};

vector<int> optimal_points(vector<Segment> &segments) {
  vector<int> points;
  //write your code here
  int included[segments.size()];
  for(int i=0; i<segments.size(); i++) included[i] = 0;
  

  for (size_t i = 0; i < segments.size(); ++i) {
    // points.push_back(segments[i].start);
    // points.push_back(segments[i].end);
    int current = -1;

    for(int j = 0; j < segments.size(); j++){
      if(current == -1 and !included[j]) current = segments[j].end;
      else if(!included[j] and current > segments[j].end)  current = segments[j].end;
    }

    // std::cout << current << "\n";

    if(current == -1) break;
    else{
      points.push_back(current);
      for(int j=0; j < segments.size(); j++){
        if(!included[j] and segments[j].start <= current and segments[j].end >= current) included[j] = 1;
      }

    }
  }
  return points;
}

int main() {
  int n;
  std::cin >> n;
  vector<Segment> segments(n);
  for (size_t i = 0; i < segments.size(); ++i) {
    std::cin >> segments[i].start >> segments[i].end;
  }
  vector<int> points = optimal_points(segments);
  std::cout << points.size() << "\n";
  for (size_t i = 0; i < points.size(); ++i) {
    std::cout << points[i] << " ";
  }
}
