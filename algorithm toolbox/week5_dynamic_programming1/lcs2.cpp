#include <iostream>
#include <vector>

using std::vector;

int lcs2_helper(vector<int> &a, vector<int> &b, int i, int j){
  if(i == a.size() or j == b.size()) return 0;

  int array[i][j];

  if(a[i] == b[j]) return 1 + lcs2_helper(a,b, i+1, j+1);
  else return std::max(lcs2_helper(a,b,i+1,j), lcs2_helper(a,b,i,j+1));
}


int lcs2(vector<int> &a, vector<int> &b) {
  //write your code here
  int n = a.size();
  int m = b.size();
  int array[n+1][m+1];

  for(int i=0; i<=n; i++) array[i][0] = 0;
  for(int j=0; j<=m; j++) array[0][j] = 0;

  for(int i=1; i<=n; i++)
    for(int j=1; j<=m; j++){
      if(a[i-1] == b[j-1]) array[i][j] = array[i-1][j-1]+1;
      else array[i][j] = std::max(array[i-1][j], array[i][j-1]);
    }

    return array[n][m];









  // return lcs2_helper(a, b, 0, 0);
}

int main() {
  size_t n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < n; i++) {
    std::cin >> a[i];
  }

  size_t m;
  std::cin >> m;
  vector<int> b(m);
  for (size_t i = 0; i < m; i++) {
    std::cin >> b[i];
  }

  std::cout << lcs2(a, b) << std::endl;
}
