#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#include <set>
#include <queue>

using std::vector;
using std::pair;
using std::stack;
using std::set;
using std::queue;


//TO FIND SINK AT ANY STAGE IN GRAPH(after removing used vertices)
vector<int> find_sink(vector<vector<int> >&adj, vector<int> &used){
  int n = adj.size();
  vector<set<int> > outgoing(n);

  for(int i=0; i<n; i++){
    if(used[i]) continue;


    vector<int> visit(n, 0);
    queue<int>current;
    visit[i]=1;
    current.push(i);
    while(!current.empty()){
      int v = current.front();
      current.pop();
      for(int j=0; j<adj[v].size(); j++){
        int e = adj[v][j];
        if(used[e]) continue;

        if(!visit[e]){
          current.push(e);
          visit[e] = 1;
        }
        outgoing[i].insert(e);
      }
    }
  }

  vector<int> sinks;

  for(int i=0; i<n; i++){
    if(outgoing[i].size() == 0 and !used[i]) {
      sinks.push_back(i);
      used[i] = 1;
    }
  }

  return sinks;
}


//TO FIND SOURCES IN GRAPH(given as adjacency list)
vector<int> find_sources(vector<vector<int> >&adj){
  int n = adj.size();
  vector<vector<int> > incoming(n, vector<int>());

  for (int i = 0; i < n; ++i)
    for(auto it=adj[i].begin(); it != adj[i].end(); it++)
      incoming[*it].push_back(i);      

  vector<int> source;
  for(int i=0; i<n; i++)
    if(incoming[i].size() == 0)
      source.push_back(i);

  return source;
}


//TO PRINT VECTORS
void print(vector<int> &v){
  for(auto it=v.begin(); it != v.end(); it++)
    std::cout<<*it+1<<" ";
    std::cout<<"\n";
}


//TO CONCATENATE TWO VECTORS
vector<int> vec_concat(vector<int>a, vector<int>b){
  for(auto it=b.begin(); it != b.end(); it++)
    a.push_back(*it);
  return a;
}


//DFS
vector<int> dfs(vector<vector<int> > &adj, vector<int> &used, int src) {
  //write your code here
  vector<int> ans;
  ans.push_back(src);

  int numchild=0;
  for(int i= 0; i < adj[src].size(); i++){
    int e = adj[src][i];
      if(!used[e]) {
        numchild++;
      }
  }

  //CHECKING SINK NODE
  if(numchild == 0) {
    return ans;
  }


  vector<vector<int> > bacche(numchild, vector<int>());

  int b=0;
  for(int i= 0; i < adj[src].size(); i++)
    {
      int e = adj[src][i];
      if(!used[e]) {
        used[e]=1;
        bacche[b] = dfs(adj, used, e);
        b++;
      }
    }

  // concat dfs of children in opposite order to remove common child problem
  for(int i=numchild-1; i>=0; i--){
    ans = vec_concat(ans, bacche[i]);
  } 
  return ans;
}

   
vector<int> new_toposort(vector<vector<int> > adj) {
   vector<int> used(adj.size(), 0);
   vector<int> order;
   // first find all sources
   vector<int> source = find_sources(adj);

   //for all sources find their order
   for(int i=0; i<source.size(); i++){
    used[source[i]]=1;
    vector<int> ans = dfs(adj,used, source[i]);
    order.insert(order.begin(), ans.begin(), ans.end());
   }
   return order;
}



vector<int> toposort(vector<vector<int> > adj) {

  vector<int> used(adj.size(), 0);
  vector<int> order;

  //write your code here
  int n = adj.size();
  
  while(order.size() < n){
    vector<int> ans = find_sink(adj, used);
    order.insert(order.begin(), ans.begin(), ans.end());
  }

  return order;
}


int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
  }
  // vector<int> order = toposort(adj);
  vector<int> order = new_toposort(adj);
  for (size_t i = 0; i < order.size(); i++) {
    std::cout << order[i] + 1 << " ";
  }
}
