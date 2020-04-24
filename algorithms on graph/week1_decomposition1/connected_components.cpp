#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::pair;

int number_of_components(vector<vector<int> > &adj) {
  // std::cout<< "ENTERED...\n";
  //write your code here
  int n = adj.size();
  int visited[n];
  for(int i=0; i<n; i++) visited[i] = 0;

  int num_visited = 0;
  int smallest_unvisited = 0;
  int components = 0;

  while(num_visited < n){

    //RESET smallest_unvisited
    for(int i=smallest_unvisited; i<n; i++){
      if(!visited[i]){
        smallest_unvisited = i;
        break;
      }
    }

    // Make new buffer
    std::queue<int> buffer;
    buffer.push(smallest_unvisited);
    num_visited++;
    components++;
    visited[smallest_unvisited] = 1;

    while(!buffer.empty()){
      // std::cout <<" num_visited = " << num_visited << "\n";
      int v = buffer.front();
      buffer.pop();

      for(int i=0; i<adj[v].size(); i++){
        if(visited[adj[v][i]]) continue;
        else {
          buffer.push(adj[v][i]);
          num_visited++;
          visited[adj[v][i]] = 1;
        }
      }
    }
  }

  return components;
}

int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }
  std::cout << number_of_components(adj)<< "\n";
}
