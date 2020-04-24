#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::pair;


int reach(vector<vector<int> > &adj, int x, int y) {
  //write your code here
  std::queue<int> buffer;
  buffer.push(x);


  if( x == y ) return 1;
  
  int n = adj.size();
  int visited[n];

  for(int i=0; i<n; i++)
    visited[i] = 0;

  visited[x] = 1;


  while(!buffer.empty()){
    int v = buffer.front();
    buffer.pop();
    
    for(int i=0; i<adj[v].size(); i++){
      if(visited[adj[v][i]]) continue;
      else if(adj[v][i] == y) return 1;
      else {
        buffer.push(adj[v][i]);
        visited[adj[v][i]] = 1;
      }
    }
   }

  return 0;
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
  int x, y;
  std::cin >> x >> y;
  std::cout << reach(adj, x - 1, y - 1) << "\n";
}
