#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <queue>

using namespace std;

using std::cin;
using std::cout;
using std::endl;
using std::make_pair;
using std::pair;
using std::string;
using std::vector;

struct Point
{
	int pos;
	string str;

	Point(int p, string s){ pos=p; str=s; }
};

struct mycomparator
{
	bool operator()(Point& p1, Point& p2)
	{	
		// return true if s1 is smaller than s2
		return p1.str > p2.str;
	}
};

// Build suffix array of the string text and
// return a vector result of the same length as the text
// such that the value result[i] is the index (0-based)
// in text where the i-th lexicographically smallest
// suffix of text starts.
vector<int> BuildSuffixArray(string& text) {
  vector<int> result;
  // Implement this function yourself
  int n = text.size();
  priority_queue<Point, vector<Point>, mycomparator>q;
  for(int i=0; i<n; i++)
  	q.push(Point(i, text.substr(i, n-i)));

  for(int i=0; i<n; i++){
  	cout << q.top().pos << " ";
  	q.pop();
  }

  return result;
}

int main() {
  string text;
  cin >> text;
  cout << text.size() << endl;
  vector<int> suffix_array = BuildSuffixArray(text);
  for (int i = 0; i < suffix_array.size(); ++i) {
    cout << suffix_array[i] << ' ';
  }
  cout << endl;
  return 0;
}
