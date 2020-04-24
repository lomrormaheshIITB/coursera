#include <algorithm>
#include <iostream>
#include <vector>
// #include <cstdlib>
// #include <iostream>
// #include <time.h>
#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif

class Node;

class Node {
public:
    int key;
    Node *parent;
    std::vector<Node *> children;

    Node() {
      this->parent = NULL;
    }

    void setParent(Node *theParent) {
      parent = theParent;
      parent->children.push_back(this);
    }
};

int tree_height(Node  &node){
  // std::cout<<"RUNning......\n";
  if(node.children.size() == 0) return 1;
  else{
    int max_height = 0;
    for(int i=0; i<node.children.size(); i++){
      max_height = std::max(max_height, tree_height(*node.children[i]));
    }
    return 1 + max_height;
  }
}


int main_with_large_stack_space() {
  std::ios_base::sync_with_stdio(0);
  int n;
  int root;
  std::cin >> n;

  std::vector<Node> nodes;
  nodes.resize(n);
  for (int child_index = 0; child_index < n; child_index++) {
    int parent_index;
    std::cin >> parent_index;
    if (parent_index >= 0)
      nodes[child_index].setParent(&nodes[parent_index]);
    else
      root = child_index;
    nodes[child_index].key = child_index;
  }

  // clock_t start, end;
  // double cpu_time_used1, cpu_time_used2;
  // start = clock();
  // Replace this code with a faster implementation
  // int maxHeight = 0;
  // for (int leaf_index = 0; leaf_index < n; leaf_index++) {
  //   int height = 0;
  //   for (Node *v = &nodes[leaf_index]; v != NULL; v = v->parent)
  //     height++;
  //   maxHeight = std::max(maxHeight, height);
  // }
    
  // std::cout << maxHeight << std::endl;

  // end = clock();
  // cpu_time_used1 = ((double) (end - start)) / CLOCKS_PER_SEC;
  //-----------------*************------------------------

  // int num_child_root = nodes[root].children.size();
  // std::cout<<"--------=  "<<num_child_root<<"\n";

  // start = clock();
  int tree_hght = tree_height(nodes[root]);
  std::cout<< tree_hght<<"\n";
  // end = clock();
  // cpu_time_used2 = ((double) (end - start)) / CLOCKS_PER_SEC;

  // std::cout << cpu_time_used1 << " "<<cpu_time_used2 << "\n";
  return 0;
}

// void test_soluton(){
//   std::ios_base::sync_with_stdio(0);
//   int n = 1000;
//   int root = 314;
//   std::vector<Node> nodes;
//   nodes.resize(n);
//   for (int child_index = 0; child_index < n; child_index++) {
//     int parent_index;
//     // std::cin >> parent_index;
//     parent_index = std::rand() % 9999;
//     if(child_index == root) parent_index = -1;
//     if (parent_index >= 0)
//       nodes[child_index].setParent(&nodes[parent_index]);
//     else
//       root = child_index;
//     nodes[child_index].key = child_index;
//   }

//   // SOLUTION1
//   int maxHeight = 0;
//   for (int leaf_index = 0; leaf_index < n; leaf_index++) {
//     int height = 0;
//     for (Node *v = &nodes[leaf_index]; v != NULL; v = v->parent)
//       height++;
//     maxHeight = std::max(maxHeight, height);
//   }
    
//   std::cout << maxHeight << std::endl;
//   int tree_hght = tree_height(nodes[root]);
//   std::cout<< tree_hght<<"\n";
//   return ;

//   //SOLUTION2
// }

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
  // test_soluton();
}
