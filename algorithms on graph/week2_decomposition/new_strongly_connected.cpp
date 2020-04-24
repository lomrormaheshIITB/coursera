#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <set>

using std::vector;
using std::pair;
using std::queue;
using std::set;

//DFS of G
void dfs(vector<vector<int> >&adj, vector<int>&used, vector<int>&post_order, int src){
	// std::cout<<"ENTER DFS....\n";
	// std::cout<<"SOURCE = " << src+1 <<"\n";
	used[src]=1;

	for(int i= 0; i < adj[src].size(); i++){
	    int e = adj[src][i];
	    if(!used[e]) dfs(adj,used,post_order,e);
	}
	post_order.push_back(src);

	return;
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

//TO PRINT SETS
void print_set(set<int> &v){
  for(auto it=v.begin(); it != v.end(); it++)
    std::cout<<*it+1<<" ";
    std::cout<<"\n";
}

vector<int> intersection(set<int>&a, set<int>&b){
  vector<int>result;
  set<int>::iterator f1 = a.begin();
  set<int>::iterator l1 = a.end();
  set<int>::iterator f2 = b.begin();
  set<int>::iterator l2 = b.end();

  while(f1 != l1 and f2 != l2){
    if(*f1 > *f2) f2++;
    else if(*f1 < *f2) f1++;
    else{
      result.push_back(*f1);
      f1++;
      f2++;
    }
  }

  return result;
}

int explore(vector<vector<int>>&adj, vector<vector<int>>&inc_adj, vector<int>&used, int x){
	// used[x]=1;
	// return 1;

	int n = adj.size();
	set<int>outgoing;
	outgoing.insert(x);

	vector<int>out_visit(n,0);
	queue<int> out_queue;
	out_queue.push(x);

	while(!out_queue.empty()){
		int v = out_queue.front();
		out_queue.pop();

		for(int i=0; i<adj[v].size(); i++){
			int e = adj[v][i];
			if(used[e]) continue;
			if(!out_visit[e]) out_queue.push(e);
			outgoing.insert(e);
			out_visit[e]=1;
		}
	}


	set<int>incoming;
	incoming.insert(x);
	vector<int>inc_visit(n,0);
	queue<int> inc_queue;
	inc_queue.push(x);

	while(!inc_queue.empty()){
		int v = inc_queue.front();
		inc_queue.pop();

		for(int i=0; i<inc_adj[v].size(); i++){
			int e = inc_adj[v][i];
			if(used[e]) continue;
			if(!inc_visit[e]) inc_queue.push(e);
			incoming.insert(e);
			inc_visit[e]=1;
		}
	}

	// SCC of 'x'
	vector<int> scc = intersection(incoming, outgoing);
	for(auto it=scc.begin(); it != scc.end(); it++)
		used[*it]=1;

	// std::cout<<"EXPLORING NODE=" << x+1 << "\n";
	// std::cout << scc.size()<<"\n";
	// std::cout << incoming.size()<<"\n";
	// print_set(incoming);
	// std::cout << outgoing.size()<<"\n";
	// print_set(outgoing);
	// for(auto it=scc.begin(); it != scc.end(); it++)
		// std::cout<<*it+1 << " ";
	// std::cout<<"\n";
	return scc.size();
}


int number_of_strongly_connected_components(vector<vector<int> > adj) {
  int result = 0;

  //BUILDING G'(reverse of G) = O(E)
  int n = adj.size();
  vector<vector<int> > rev_adj(n);
  for(int i=0; i<n; i++){
  	for(int j=0; j<adj[i].size(); j++){
  		int x = adj[i][j];
  		rev_adj[x].push_back(i);
  	}
  }

  //CAlCULATE SOURCES
  vector<int>source_Gr = find_sources(rev_adj);
  vector<int>source_G = find_sources(adj);
  // std::cout<<"SOURCES of Gr:\n";
  // print(source_Gr);

  // return 1;

  vector<int>used(n, 0);
  vector<int>exp_used(n, 0);
  vector<int>post_order;


  //IF SOURCES PRESENT in Gr
	if(source_Gr.size()){
 		for(int i=0; i<source_Gr.size(); i++){
  			dfs(rev_adj, used, post_order, source_Gr[i]);
  		}
	}

  //IF NO SOURCES in Gr
 	else if(source_G.size()){
 		for(int i=0; i<source_G.size(); i++){
  			dfs(adj, used, post_order, source_G[i]);
  		}
	}

	// NO SOUCES IN BOTH
	else 
  		dfs(adj, used, post_order, 0);

  // std::cout<<"POST ORDER:\n";
  // print(post_order);

  //BUILDING INCOMING ADJ
  // rev_adj works same as incoming_adj

  // PRINT INCOMING AND OUGOING
  // std::cout<<"OUTGOING ADJ.....\n";
  // for(int i=0; i<n; i++) print(adj[i]);
  // std::cout<<"INCOMING ADJ.....\n";
  // for(int i=0; i<n; i++) print(rev_adj[i]);
  // std::cout<<"----------------\n";

  int num_explored = 0;
  int index = 0;

  while(num_explored < n){
  	result++;
  	// std::cout<<"index = " << index << "\n";
  	num_explored += explore(adj, rev_adj, exp_used, post_order[index]);

  	for(int i=index+1; i<n; i++){
  		if(!exp_used[post_order[i]]){
  			index = i;
  			break;
  		}
  	}
  }


  return result;
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
  std::cout << number_of_strongly_connected_components(adj)<<"\n";
}