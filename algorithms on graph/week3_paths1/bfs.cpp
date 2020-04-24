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

int distance(vector<vector<int> > &adj, int s, int t) {
  //write your code here

	int dist = 1;
	vector<int> visited(adj.size(),0);
	queue<int> buffer;
	Enqueue(buffer, s);
	Enqueue(buffer, -1);
	visited[s]=1;

	while(!buffer.empty()){
		// print_queue(buffer);
		int x = Dequeue(buffer);
		if(x == -1){
			if(buffer.size() != 0){
				dist++;
				Enqueue(buffer, -1);
				continue;	
			}
		}
		else{
			for(int i=0; i<adj[x].size(); i++){
				int v = adj[x][i];
				if(v == t) return dist;
				if(!visited[v]){
					Enqueue(buffer, v);
					visited[v]=1;
				}
			}	
		}
		
	}
  return -1;
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
  int s, t;
  std::cin >> s >> t;
  s--, t--;
  std::cout << distance(adj, s, t);
}
