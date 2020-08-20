#include <string>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

typedef map<char, int> edges;
typedef vector<edges> trie;

trie build_trie(vector<string> & patterns) {
  trie t;
  // write your code here
  int n = patterns.size();

  int global_label = 1;
  int m; // current_pattern_size
  int current_node;
  char current_symbol;

  // insert root node with no edges
  edges new_egde;
  t.push_back(new_egde);

  for(int i=0; i<n; i++){
  	m = patterns[i].size();
  	current_node = 0;
  	
  	for(int j=0; j<m; j++){
  		current_symbol = patterns[i][j];

  		if(t[current_node].find(current_symbol) != t[current_node].end()){
  			current_node = t[current_node].find(current_symbol)->second;
  		}
  		else{
  			t[current_node].insert({current_symbol, global_label});
  			current_node = global_label;
  			edges new_egde;
  			t.push_back(new_egde);
  			global_label++;
  		}
  	}
  }
  return t;
}

int main() {
  size_t n;
  std::cin >> n;
  vector<string> patterns;
  for (size_t i = 0; i < n; i++) {
    string s;
    std::cin >> s;
    patterns.push_back(s);
  }

  trie t = build_trie(patterns);
  for (size_t i = 0; i < t.size(); ++i) {
    for (const auto & j : t[i]) {
      std::cout << i << "->" << j.second << ":" << j.first << "\n";
    }
  }
  return 0;
}