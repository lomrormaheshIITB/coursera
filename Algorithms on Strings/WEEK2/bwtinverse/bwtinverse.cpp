#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <map>

using namespace std;

void InverseBWT(const string& bwt) {
  string text = "";

  // size of input bwt string
  int n = bwt.size();  

  // keep track of total occurances of A,C,G,T
  int num[4] = {0,0,0,0};

  //
  map<int, int> mymap;
  mymap.insert({0, 0});
  mymap.insert({2, 1});
  mymap.insert({6, 2});
  mymap.insert({19, 3});



  //LastColumn is bwt, FirstColumn is lexicographically sorted bwt
  //LastToFirst is Mapping of k-th latter from lastColumn to FirstColumn
  vector<char>LastColumn(n);
  vector<char>FirstColumn;
  vector<int>LastToFirst(n);

  // Fill LastColumn and find number of occurances of all letters
  for(int i=0; i<n; i++){
  	LastColumn[i] = bwt[i];
  	if(bwt[i] != '$'){
  		num[mymap.find(toascii(bwt[i]-65))->second]++;
  	}
  }

  // keep track of k-th occurance of letter for LastToFirst Mapping
  int counter[4] = {1, 1+num[0], 1+num[0]+num[1], 1+num[0]+num[1]+num[2]};

  // Compute FirstColumn
  FirstColumn.push_back('$');;
  for(int i=0; i<num[0]; i++) FirstColumn.push_back('A');
  for(int i=0; i<num[1]; i++) FirstColumn.push_back('C');
  for(int i=0; i<num[2]; i++) FirstColumn.push_back('G');
  for(int i=0; i<num[3]; i++) FirstColumn.push_back('T');


  // Computing Mapping from LastColumn to FirstColumn
  for(int i=0; i<n; i++){
  	if(bwt[i] == '$')
  		LastToFirst[i] = 0;
  	else
  		LastToFirst[i] = counter[mymap.find(toascii(bwt[i]-65))->second]++;
  }

  // Find Inverse BWT and then reverse back to get original text
  vector<char>temp(n);
  int current = 0;
  for(int i=0; i<n; i++){
  	temp[i] = FirstColumn[current];
  	current = LastToFirst[current];
  }

  for(int i=0; i<n; i++) cout << temp[n-1-i];
}

int main() {
  string bwt;
  cin >> bwt;
  InverseBWT(bwt);
  cout << endl;
  return 0;
}
