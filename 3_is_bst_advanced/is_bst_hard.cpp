#include <algorithm>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

struct Node {
  int key;
  int left;
  int right;

  Node() : key(0), left(-1), right(-1) {}
  Node(int key_, int left_, int right_) : key(key_), left(left_), right(right_) {}
};

void inorder_method(const vector<Node>&tree, int index, vector<int>&result, bool &flag){

    // CHECK FLAG
    if(!flag) return;

    // CHECK IF NODE IS NULL
    if(index == -1) return;

    // CHECK FOR NODE
    int left_child = tree[index].left; 
    if(left_child != -1)
      if(tree[left_child].key >= tree[index].key){
        flag = false;
        return;
      } 

    inorder_method(tree, tree[index].left, result, flag);
    if(!flag) return;
    result.push_back(tree[index].key);
    inorder_method(tree, tree[index].right, result, flag);
    return; 
}

bool IsBinarySearchTree(const vector<Node>& tree) {
  // Implement correct algorithm here
  // BASE CASE 
  if(tree.size() == 0) return true;

  
  vector<int>result;
  bool flag = true;

  // CHECK FOR ROOT
  int left_child = tree[0].left; 
  if(left_child != -1)
    if(tree[left_child].key >= tree[0].key) return false;

  // RECURSIVE 
  inorder_method(tree, tree[0].left, result, flag);
  if(!flag) return false;
  result.push_back(tree[0].key);
  inorder_method(tree, tree[0].right, result, flag);
  if(!flag) return false;


  // CHECK INORDER TRANSVERSAL
  for(int i=0; i<result.size()-1; i++)
    if(result[i] > result[i+1]) return false;

  return true;
}

int main() {
  int nodes;
  cin >> nodes;
  vector<Node> tree;
  for (int i = 0; i < nodes; ++i) {
    int key, left, right;
    cin >> key >> left >> right;
    tree.push_back(Node(key, left, right));
  }
  if (IsBinarySearchTree(tree)) {
    cout << "CORRECT" << endl;
  } else {
    cout << "INCORRECT" << endl;
  }
  return 0;
}
