#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::queue;


void Enqueue(queue<int> &q, int x){
  q.push(x);
}

int Dequeue(queue<int> &q){
  int x = q.front();
  q.pop();
  return x;
}

void print_queue(queue<int> &q){
  queue<int> p(q);
  
  while(!p.empty()){
    std::cout << p.front()+1 << " ";
    p.pop();
  } 
  std::cout << "\n";
}

int compute_smallest_unvisited(vector<int> &color, int smallest_unvisited){
  int result = -1;
  for(int i=smallest_unvisited+1; i<color.size(); i++){
    if(color[i] == -1) return i;
  }
  return result;
}

int Switch_color(int current_color){
  if(current_color) return 0;
  return 1;
}

int bipartite(vector<vector<int> > &adj) {
  //write your code here

  int n = adj.size();
  queue<int> buffer;
  vector<int> color(n, -1);
  int smallest_unvisited = 0;
  int num_visited = 0;
  int current_color;

  // std::cout << "OK_1\n";
  while(num_visited < n){
    current_color = 0;
    Enqueue(buffer, smallest_unvisited);
    color[smallest_unvisited]=current_color;
    current_color = Switch_color(current_color);
    num_visited++;
    // print_queue(buffer);
      
    while(!buffer.empty()){
      int x = Dequeue(buffer);
      int c = color[x];
      current_color = Switch_color(c);

      for(int i=0; i<adj[x].size(); i++){
        int v = adj[x][i];
        if(color[v] == -1){
          color[v] = current_color;
          Enqueue(buffer, v);
          num_visited++;
        }
        else if(color[v] == c) return 0 ;
      }
    }

    smallest_unvisited = compute_smallest_unvisited(color, smallest_unvisited);
  }
  // std::cout << "OK_2\n";

  return 1;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }
  std::cout << bipartite(adj);
}
