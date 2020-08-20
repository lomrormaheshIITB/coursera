#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <cassert>
#include <cstdio>

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

//
vector <int> solve (const string& text, int n, vector <string>& patterns)
{
  vector <int> result;
  int text_size = text.size();
  // write your code here
  trie t = build_trie(patterns);

  // PRINT TRIE
  // cout << "TRIE:\n";
  // cout << "size = " << t.size() << endl;
  // for(int i=0; i<t.size(); i++){
  //   cout << i << ":";
  //   map<char,int>:: iterator it = t[i].begin();
  //   for( 1; it!= t[i].end(); it++){
  //     cout << "(" << it->first << "," << it->second << ") "; 
  //   }
  //   cout << endl;
  // }

  // cout <<"------------------------------\n";

  int current_node;
  char current_symbol;
  int l; // to iterate from i


  for(int i=0; i<text_size; i++){
    current_node = 0;
    current_symbol = text[i];
    l = i;

    while(true){

      // check for leaf
      if(t[current_node].size() == 0){
        result.push_back(i);
        break;
      }
      // symbol match
      else if(t[current_node].find(current_symbol) != t[current_node].end()){
          current_node = t[current_node].find(current_symbol)->second;
          l++;
          if(l == text_size){
            if(t[current_node].size() == 0)
              result.push_back(i);
            break;
          } 
          current_symbol = text[l];
      }
      // symbol not match
      else{
        break;
      }

    }
  }

  return result;
}


// ------------------------------------------------------------------------------
int main (void)
{
  string t;
  cin >> t;

  int n;
  cin >> n;

  vector <string> patterns (n);
  for (int i = 0; i < n; i++)
  {
    cin >> patterns[i];
  }

  vector <int> ans;
  ans = solve (t, n, patterns);

  for (int i = 0; i < (int) ans.size (); i++)
  {
    cout << ans[i];
    if (i + 1 < (int) ans.size ())
    {
      cout << " ";
    }
    else
    {
      cout << endl;
    }
  }

  return 0;
}
