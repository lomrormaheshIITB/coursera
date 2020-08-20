#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <map>
#include <queue>
#include <set>

using namespace std;

int node_number = 0;
// PRINT VECTOR
void print_vector(vector<int> &v){
  cout << "PRINTING...\n";
  for(int i=0; i<v.size(); i++)
    cout << v[i] << " ";
  cout << endl;
}
// -------------------------------------------------------------------------

class SuffixTreeNode
{
public:
  SuffixTreeNode * parent;
  map<char, SuffixTreeNode *> children;
  int stringDepth;
  int edgeStart;
  int edgeEnd;
  int number;
  int leaf_value;

  SuffixTreeNode(map<char, SuffixTreeNode *> c, SuffixTreeNode * p, int d, int s=0, int e=0, int l=-1){
    parent = p; children = c; stringDepth = d; edgeStart = s; edgeEnd = e;
    number = node_number++; leaf_value = l;
  }
};

// 
SuffixTreeNode * CreateNewLeaf(SuffixTreeNode * node, const string &S, int suffix) {
  int n = S.size();
  SuffixTreeNode * leaf = new SuffixTreeNode(
    {}, node, n - suffix, suffix + node->stringDepth, n-1, suffix);

  node->children.insert({S[leaf->edgeStart], leaf});
  return leaf;

}

// 
SuffixTreeNode * BreakEdge(SuffixTreeNode * node, const string  &S, int start, int offset) {

  char startChar = S[start];
  char midChar = S[start + offset];
  SuffixTreeNode * midNode = new SuffixTreeNode(
    {}, node, node->stringDepth + offset, start, start + offset - 1);

  midNode->children.insert({midChar, node->children[startChar]});
  node->children[startChar]->parent = midNode;
  node->children[startChar]->edgeStart += offset;
  node->children[startChar] = midNode;

  return midNode;
}

//
SuffixTreeNode * STFromSA(const string &S, const vector<int> &order, vector<int> &lcpArray){
  //  Suffix Tree From Suffix Array
  int n = S.size();

  // ROOT
  SuffixTreeNode * root = new SuffixTreeNode({}, NULL, 0, -1, -1);

  int lcpPrev = 0;
  SuffixTreeNode * curNode = root;

  for(int i=0; i<n; i++){
    int suffix = order[i];

    while(curNode->stringDepth > lcpPrev)
      curNode = curNode->parent;

    if(curNode->stringDepth == lcpPrev)
      curNode = CreateNewLeaf(curNode, S, suffix);
    else {
      int edgeStart = order[i-1] + curNode->stringDepth;
      int offset = lcpPrev - curNode->stringDepth;
      SuffixTreeNode * midNode = BreakEdge(curNode, S, edgeStart, offset);
      curNode = CreateNewLeaf(midNode, S, suffix);
    }

    if(i < n-1)
      lcpPrev = lcpArray[i];

  }

  return root;
}

// -------------------------------------------------------------------------

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
// 
vector<int> InvertSuffixArray(const vector<int> &order){
  int n = order.size();
  vector<int> pos(n);
  for(int i=0; i<n; i++)
    pos[order[i]] = i;
  return pos;
}

// 
int LCPOfSuffixes(const string &S, int i, int j, int equal){
  int lcp = max(0, equal);
  int n = S.size();

  while(i+lcp < n and j+lcp < n)
    if(S[i+lcp] == S[j+lcp])
      lcp++;
    else
      break;

  return lcp;
}

// 
vector<int> ComputeLCPArray(const string &S, const vector<int> &order){
  int n = S.size();
  vector<int> lcpArray(n);
  int lcp = 0;
  vector<int> posInOrder = InvertSuffixArray(order);
  int suffix = order[0];

  for(int i=0; i<n; i++){
    int orderIndex = posInOrder[suffix];
    if(orderIndex == n-1){
      lcp = 0;
      suffix = (suffix + 1) % n;
      continue;
    }

    int nextSuffix = order[orderIndex + 1];
    lcp = LCPOfSuffixes(S, suffix, nextSuffix, lcp-1);
    lcpArray[orderIndex] = lcp;
    suffix = (suffix + 1) % n;
  }

  return lcpArray;
}

// PRINT TREE
void print_tree(SuffixTreeNode * root) {
// parent, children, startDepth, edgeStart, edgeEnd, number

    queue<SuffixTreeNode *> window;
    window.push(root);

    SuffixTreeNode * node;

    while(!window.empty()){
      node = window.front();
      window.pop();

      cout << "(" << node->number << "," 
        << node->stringDepth << "," << node->edgeStart << ","
        << node->edgeEnd << "," << node->leaf_value << ") =  (";

      for(auto it=node->children.begin(); it!=node->children.end(); it++){
        window.push(it->second);
        cout << "{" << it->first << "," << it->second->number << "}, ";
      }

      cout << ")\n";
    }

  return;
}

// find leafs from given node
void findLeafs(SuffixTreeNode * node, set<int> &result){
  if(node == NULL) return;

  if(node->children.size() == 0){
    // cout << node->number << " " << node->leaf_value << endl;
    result.insert(node->leaf_value);
  }
  else
    for(auto it=node->children.begin(); it!=node->children.end(); it++)
      findLeafs(it->second, result);
  return;
}

// 
// parent, children, startDepth, edgeStart, edgeEnd, number
void find(const string& pattern, const string& text, int pos, int p, SuffixTreeNode * node, set<int> &result) {
  // no such children
  // cout << node->number << endl;
  if(node->children.find(pattern[pos]) == node->children.end()) return;

  node = node->children.find(pattern[pos])->second;
  int pattern_left_len = p - pos;
  int edge_size = node->edgeEnd - node->edgeStart + 1;

  // pattern end in current edge
  if(pattern_left_len <= edge_size){
    if(pattern.substr(pos, pattern_left_len).compare(text.substr(node->edgeStart, pattern_left_len)) == 0)
      findLeafs(node, result);
  }

  // pattern does not end in current edge
  else if(pattern.substr(pos, edge_size).compare(text.substr(node->edgeStart, edge_size)) == 0)
      find(pattern, text, pos+edge_size, p, node, result);
}

// ---------------------------------------------------------------------------
int main() {
  char buffer[100001];
  scanf("%s", buffer);
  string text = buffer;
  text += '$';
  vector<int> suffix_array = BuildSuffixArray(text);
  int pattern_count;
  scanf("%d", &pattern_count);
  vector<bool> occurs(text.length(), false);
// ----------------------------
  vector<int>lcpArray = ComputeLCPArray(text, suffix_array);
  SuffixTreeNode * root = STFromSA(text, suffix_array, lcpArray);
  set<int> answer;

  for(int i=0; i<pattern_count; i++){
    scanf("%s", buffer);
    string pattern = buffer;
    find(pattern, text, 0, pattern.size(), root, answer);
  }

  for(auto it=answer.begin(); it!=answer.end(); it++)
    cout << *it << " ";

  cout << endl;

  return 1;


// ----------------------------
  // for (int pattern_index = 0; pattern_index < pattern_count; ++pattern_index) {
  //   scanf("%s", buffer);
  //   string pattern = buffer;
  //   vector<int> occurrences = FindOccurrences(pattern, text, suffix_array);
  //   for (int j = 0; j < occurrences.size(); ++j) {
  //     occurs[occurrences[j]] = true;
  //   }
  // }
  // for (int i = 0; i < occurs.size(); ++i) {
  //   if (occurs[i]) {
  //     printf("%d ", i);
  //   }
  // }
  // printf("\n");
  return 0;
}
