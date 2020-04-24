#include <iostream>
#include <vector>

using std::vector;

int optimal_weight(int W, const vector<int> &w) {
  //write your code here
  int N = w.size();
  // int gold[W+1][N+1];

  int n = N+1;
  int wt = W+1;
  vector<int> gold(n * wt);

  int remaining_weight = W;

  // for(int i=0; i<=W; i++) gold[i][0] = 0;  // no bar selected
  // for(int j=0; j<=N; j++) gold[0][j] = 0;  // W = 0
  for(int i=0; i<=W; i++) gold[i * n + 0] = 0;  // no bar selected
  for(int j=0; j<=N; j++) gold[0 * n + j] = 0;  // W = 0


  for(int i=1; i<=W; i++){
  	for(int j=1; j<=N; j++){
  		gold[i * n + j] = gold[i * n + j-1];
  		if(w[j-1] <= i){
  			int i_dash = i - w[j-1];
  			gold[i * n + j] = std::max(gold[i * n + j], gold[i_dash * n + j-1] + w[j-1]);
  		}
  	}
  }


  return gold[W * n + N];
}

int main() {
  int n, W;
  std::cin >> W >> n;
  vector<int> w(n);
  for (int i = 0; i < n; i++) {
    std::cin >> w[i];
  }
  std::cout << optimal_weight(W, w) << '\n';
}
