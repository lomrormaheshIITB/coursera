#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <map>

using namespace std;

//

// PRINT VECTOR
void print_vector(vector<int> &v){
  cout << "PRINTING...\n";
  for(int i=0; i<v.size(); i++)
    cout << v[i] << " ";
  cout << endl;
}

// 
vector<int> SortCharacters(const string &text) {
  int n = text.size();
  vector<int> order(n);

  int count[5] = {0, 0, 0, 0, 0};
  map<char, int> mymap;
  mymap.insert({'$', 0});
  mymap.insert({'A', 1});
  mymap.insert({'C', 2});
  mymap.insert({'G', 3});
  mymap.insert({'T', 4});

  for(int i=0; i<n; i++)
    count[mymap.find(text[i])->second]++;

  for(int j=1; j<5; j++)
    count[j] = count[j] + count[j-1];

  for(int i=n-1; i>=0; i--){
    int c = mymap.find(text[i])->second;
    count[c]--;
    order[count[c]] = i;
  }

  return order;
}

//
vector<int> ComputeCharClasses(const string &text, const vector<int> &order) {
  int n = text.size();
  vector<int> myclass(n);
  myclass[order[0]] = 0;

  for(int i=1; i<n; i++)
    if(text[order[i]] != text[order[i-1]])
      myclass[order[i]] = myclass[order[i-1]] + 1;
    else
      myclass[order[i]] = myclass[order[i-1]];

  return myclass;
}

// 
vector<int> SortDoubled(const string &text, const int L, const vector<int> &order, const vector<int> &myclass) {
  int n = text.size();
  vector<int> neworder(n);

  vector<int>count(n, 0);

  for(int i=0; i<n; i++)
    count[myclass[i]] = count[myclass[i]] + 1;

  for(int j=1; j<n; j++)
    count[j] = count[j] + count[j-1];


  for(int i=n-1; i>=0; i--){
    int start = (order[i] - L + n) % n;
    int cl = myclass[start];
    count[cl] = count[cl] - 1;
    neworder[count[cl]] = start;

  }

  return neworder;
}

// 
vector<int> UpdateClasses(const vector<int> &neworder, const vector<int> &myclass, int L) {
  int n = neworder.size();
  vector<int> newclass(n);

  newclass[neworder[0]] = 0;

  for(int i=1; i<n; i++){
    int cur = neworder[i];
    int prev = neworder[i-1];
    int mid = (cur+L) % n;
    int midprev = (prev+L) % n;

    if(myclass[cur] != myclass[prev] or myclass[mid] != myclass[midprev])
      newclass[cur] = newclass[prev] + 1;
    else
      newclass[cur] = newclass[prev];
  }

  return newclass;
}


// Build suffix array of the string text and
// return a vector result of the same length as the text
// such that the value result[i] is the index (0-based)
// in text where the i-th lexicographically smallest
// suffix of text starts.
vector<int> BuildSuffixArray(const string& text) {
  // Implement this function yourself
  vector<int> order = SortCharacters(text);
  vector<int> myclass = ComputeCharClasses(text, order);

  // print_vector(myclass);
  int L=1;
  int n = text.size();

  while(L<n){
    order = SortDoubled(text, L, order, myclass);
    myclass = UpdateClasses(order, myclass, L);
    L = 2*L;
  }

  return order;
}

int main() {
  string text;
  cin >> text;
  vector<int> suffix_array = BuildSuffixArray(text);
  for (int i = 0; i < suffix_array.size(); ++i) {
    cout << suffix_array[i] << ' ';
  }
  cout << endl;
  return 0;
}
