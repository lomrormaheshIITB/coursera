#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

using namespace std;


// 
vector<int> ComputePrefixFunction(string P) {
	int n = P.size();
	vector<int> prefix(n);

	int border = 0;
	prefix[0] = 0;

	 for(int i=1; i<n; i++){
	 	while(border and P[i] != P[border])
	 		border = prefix[border-1];

	 	if(P[i] == P[border])
	 		border = border + 1;
	 	else
	 		border = 0;

	 	prefix[i] = border;
	 }

	return prefix;
}

// Find all occurrences of the pattern in the text and return a
// vector with all positions in the text (starting from 0) where 
// the pattern starts in the text.
vector<int> find_pattern(const string& pattern, const string& text) {
  vector<int> result;
  // Implement this function yourself

  string new_pattern = pattern + '$' + text;
  vector<int>prefix = ComputePrefixFunction(new_pattern);

  int p = pattern.size();
  for(int i=p+1; i<new_pattern.size(); i++)
  	if(prefix[i] == p)
  		result.push_back(i-2*p);

  return result;
}

int main() {
  string pattern, text;
  cin >> pattern;
  cin >> text;
  vector<int> result = find_pattern(pattern, text);
  for (int i = 0; i < result.size(); ++i) {
    printf("%d ", result[i]);
  }
  printf("\n");
  return 0;
}
