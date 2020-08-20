#include <algorithm>
#include <cstdio>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
using std::istringstream;


// Preprocess the Burrows-Wheeler Transform bwt of some text
// and compute as a result:
//   * starts - for each character C in bwt, starts[C] is the first position 
//       of this character in the sorted array of 
//       all characters of the text.
//   * occ_count_before - for each character C in bwt and each position P in bwt,
//       occ_count_before[C][P] is the number of occurrences of character C in bwt
//       from position 0 to position P inclusive.
void PreprocessBWT(const string& bwt, 
                   map<char, int>& starts, 
                   map<char, vector<int> >& occ_count_before) {
  // Implement this function yourself

  //
  int n = bwt.size();

  // map $,A,C,G,T => 0,1,2,3,4
  map<char, int>ascii_to_index;
  ascii_to_index.insert({'$', 0});
  ascii_to_index.insert({'A', 1});
  ascii_to_index.insert({'C', 2});
  ascii_to_index.insert({'G', 3});
  ascii_to_index.insert({'T', 4});

  // compute start and occ_count_before
  int count[5] = {0,0,0,0,0};
  occ_count_before['$'].push_back(count[0]);
  occ_count_before['A'].push_back(count[1]);
  occ_count_before['C'].push_back(count[2]);
  occ_count_before['G'].push_back(count[3]);
  occ_count_before['T'].push_back(count[4]);

  // Make Count Array
  for(int i=0; i<n; i++){
    count[ascii_to_index.find(bwt[i])->second]++;
    occ_count_before['$'].push_back(count[0]);
    occ_count_before['A'].push_back(count[1]);
    occ_count_before['C'].push_back(count[2]);
    occ_count_before['G'].push_back(count[3]);
    occ_count_before['T'].push_back(count[4]);
  }

  // Make Start
  if(count[0]) starts.insert({'$', 0});
  if(count[1]) starts.insert({'A', count[0]});
  if(count[2]) starts.insert({'C', count[0] + count[1]});
  if(count[3]) starts.insert({'G', count[0] + count[1] + count[2]});
  if(count[4]) starts.insert({'T', count[0] + count[1] + count[2] + count[3]});

  // PRINT START TABLE
  // cout << "START\n";
  // if(count[0]) cout << "$=" << starts.find('$')->second << " ";
  // if(count[1]) cout << "A=" << starts.find('A')->second << " ";
  // if(count[2]) cout << "C=" << starts.find('C')->second << " ";
  // if(count[3]) cout << "G=" << starts.find('G')->second << " ";
  // if(count[4]) cout << "T=" << starts.find('T')->second << " ";
  // cout << endl;

  //PRINT COUNT ARRAY
  // cout << "COUNT ARRAY\n";
  // cout << "i   | $ A C G T\n";
  // vector<int>t1 = occ_count_before.find('$')->second;
  // vector<int>t2 = occ_count_before.find('A')->second;
  // vector<int>t3 = occ_count_before.find('C')->second;
  // vector<int>t4 = occ_count_before.find('G')->second;
  // vector<int>t5 = occ_count_before.find('T')->second;
  // for(int i=0; i<=n; i++){
  //   cout << i << "   | " << t1[i] << " " << t2[i] << " " << t3[i] << " " << t4[i] << " " << t5[i] << endl; 
  // } 

  return;
}

// Compute the number of occurrences of string pattern in the text
// given only Burrows-Wheeler Transform bwt of the text and additional
// information we get from the preprocessing stage - starts and occ_count_before.
int CountOccurrences(const string& pattern, 
                     const string& bwt, 
                     const map<char, int>& starts, 
                     const map<char, vector<int> >& occ_count_before) {
  // Implement this function yourself

  int n = bwt.size();
  int p = pattern.size();
  int top = 0;
  int bottom = n-1;

  int pattern_pos = 0;
  char symbol;


  while(top <= bottom){

      // if pattern is nonempty
      if(pattern_pos < p){
          symbol = pattern[p-1-pattern_pos];
          pattern_pos++;

          // if symbol not found 
          if(occ_count_before.find(symbol) == occ_count_before.end()) return 0;

          // if pos from top to bottom in LastColumn conatins an occurance of symbol
          int start_pos = starts.find(symbol)->second; 

          //if positions from top to bottom in LastColumn contains an occurance of symbol
          if(occ_count_before.find(symbol)->second[top+1] < occ_count_before.find(symbol)->second[bottom+1] or bwt[top] == symbol){
              top = start_pos + occ_count_before.find(symbol)->second[top];
              bottom = start_pos + occ_count_before.find(symbol)->second[bottom+1]-1;
          }
          else
              return 0;

      }
      else{
          return bottom - top + 1;
      }

  }

  return 0;
}
     

int main() {
  string bwt;
  cin >> bwt;
  int pattern_count;
  cin >> pattern_count;
  // Start of each character in the sorted list of characters of bwt,
  // see the description in the comment about function PreprocessBWT
  map<char, int> starts;
  // Occurrence counts for each character and each position in bwt,
  // see the description in the comment about function PreprocessBWT
  map<char, vector<int> > occ_count_before;
  // Preprocess the BWT once to get starts and occ_count_before.
  // For each pattern, we will then use these precomputed values and
  // spend only O(|pattern|) to find all occurrences of the pattern
  // in the text instead of O(|pattern| + |text|).
  PreprocessBWT(bwt, starts, occ_count_before);
  for (int pi = 0; pi < pattern_count; ++pi) {
    string pattern;
    cin >> pattern;
    int occ_count = CountOccurrences(pattern, bwt, starts, occ_count_before);
    printf("%d ", occ_count);
    // break;
  }
  printf("\n");
  return 0;
}
