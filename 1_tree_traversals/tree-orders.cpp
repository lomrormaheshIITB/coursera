#include <iostream>
#include <vector>

#include <algorithm>
#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif

using std::vector;
using std::ios_base;
using std::cin;
using std::cout;

class TreeOrders {
  int n;
  int root = -1;
  vector <int> key;
  vector <int> left;
  vector <int> right;

public:
  void read() {
    cin >> n;
    key.resize(n);
    left.resize(n);
    right.resize(n);
    for (int i = 0; i < n; i++) {
      cin >> key[i] >> left[i] >> right[i];
    }
  }

  void inorder_method(int root, vector<int>&result){
    if(root == -1) return;
    inorder_method(left[root], result);
    result.push_back(key[root]);
    inorder_method(right[root], result);
  } 

  void preorder_method(int root, vector<int>&result){
    if(root == -1) return;
    result.push_back(key[root]);
    preorder_method(left[root], result);
    preorder_method(right[root], result);
  }

  void postorder_method(int root, vector<int>&result){
    if(root == -1) return;
    postorder_method(left[root], result);
    postorder_method(right[root], result);
    result.push_back(key[root]);
  }

  vector <int> in_order() {
    vector<int> result;
    // Finish the implementation
    // You may need to add a new recursive method to do that

    // if root not set , find root of tree
    if(root == -1){
       // find parents of all nodes
      vector<int>parent(n,-1);
      for(int i=0; i<n; i++){
        if(left[i]+1) parent[left[i]]=i;
        if(right[i]+1) parent[right[i]]=i;
      }

      // find root element i.e. node that doesn't have parent
      for(int i=0; i<n; i++){
        if(parent[i] == -1){
          root = i;
          break;
        }
      }
    }

    inorder_method(left[root], result);
    result.push_back(key[root]);
    inorder_method(right[root], result);


    return result;
  }

  vector <int> pre_order() {
    vector<int> result;    
    // Finish the implementation
    // You may need to add a new recursive method to do that

    result.push_back(key[root]);
    preorder_method(left[root], result);
    preorder_method(right[root], result);
    
    return result;
  }

  vector <int> post_order() {
    vector<int> result;
    // Finish the implementation
    // You may need to add a new recursive method to do that

    postorder_method(left[root], result);
    postorder_method(right[root], result);
    result.push_back(key[root]);
    return result;
  }
};

void print(vector <int> a) {
  for (size_t i = 0; i < a.size(); i++) {
    if (i > 0) {
      cout << ' ';
    }
    cout << a[i];
  }
  cout << '\n';
}

int main_with_large_stack_space() {
  ios_base::sync_with_stdio(0);
  TreeOrders t;
  t.read();
  print(t.in_order());
  print(t.pre_order());
  print(t.post_order());
  return 0;
}

int main (int argc, char **argv)
{
#if defined(__unix__) || defined(__APPLE__)
  // Allow larger stack space
  const rlim_t kStackSize = 16 * 1024 * 1024;   // min stack size = 16 MB
  struct rlimit rl;
  int result;

  result = getrlimit(RLIMIT_STACK, &rl);
  if (result == 0)
  {
      if (rl.rlim_cur < kStackSize)
      {
          rl.rlim_cur = kStackSize;
          result = setrlimit(RLIMIT_STACK, &rl);
          if (result != 0)
          {
              std::cerr << "setrlimit returned result = " << result << std::endl;
          }
      }
  }
#endif

  return main_with_large_stack_space();
}

