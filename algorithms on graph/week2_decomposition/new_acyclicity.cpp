#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

using std::set;
using std::queue;
using std::vector;
using std::pair;

bool is_intersection_null(set<int>&outgoing, set<int>incoming){
	int o_size = outgoing.size();
	int i_size = incoming.size();

	if(o_size and i_size){
		set<int>::iterator o_it = outgoing.begin();
		set<int>::iterator i_it = incoming.begin();

		while(o_it != outgoing.end() and i_it != incoming.end()){
			if(*o_it == *i_it) return 0;
			else if(*o_it > *i_it) i_it++;
			else o_it++;
		}
	}
	else return 1;
}

int acyclic(vector<vector<int> > &adj){

	int n = adj.size();
	vector<set<int> > incoming(n);
	vector<set<int> > outgoing(n);


	for(int i=0; i<n; i++){
		int visit[n];
		for(int k=0; k<n; k++) visit[k]=0;
		queue<int>current;
		visit[i]=1;
		current.push(i);
		while(!current.empty()){
			int v = current.front();
			current.pop();
			for(int j=0; j<adj[v].size(); j++){
				int e = adj[v][j];
				if(!visit[e]){
					current.push(e);
					visit[e] = 1;
				}
				outgoing[i].insert(e);
				incoming[e].insert(i);
			}
		}
	}

	// flag = true :=> acyclic
	int flag = true;
	for(int i=0; i<n; i++)
		flag = flag and is_intersection_null(outgoing[i], incoming[i]);


	if(flag) return 0;
	else return 1;

}









//----------------
int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
  }
  std::cout << acyclic(adj)<< "\n";
  // std::cout << naive(adj);
  // std::cout<<std::endl;
	// srand(time(0));
  // for(int i=0; i<200; i++)  test_solution();
}
