#include <algorithm>
#include <iostream>
#include <string>
#include <queue>
#include <vector>

using namespace std;

string BWT(const string& text) {
  string result = "";

  // write your code here
  int n = text.size();
  priority_queue<string, vector<string>, greater<string>> q;

  string temp = text;
  for(int i=0; i<n; i++){
    temp = temp.substr(1, n-1) + string(1,temp[0]);
    q.push(temp);
  }

  for(int i=0; i<n; i++){
    result += q.top()[n-1];
    q.pop();
  }

  return result;
}

int main() {
  string text;
  cin >> text;
  cout << BWT(text) << endl;
  return 0;
}