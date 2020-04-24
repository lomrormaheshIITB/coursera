#include <iostream>
#include <vector>

using std::vector;

bool is_Equal(char a, char b, char c){
  if(a == b)
    if(b == c)
      return true;
  return false;
}

int lcs3(vector<int> &a, vector<int> &b, vector<int> &c) {
  //write your code here
  int n = a.size();
  int m = b.size();
  int l = c.size();
  int array[n+1][m+1][l+1];

  // for(int i=0; i<=n; i++)
  //   for(int j=0; j<=m; j++)
  //     array[i][j][0] = 0;
  // for(int i=0; i<=n; i++)
  //   for(int k=0; k<=l; k++)
  //     array[i][0][k] = 0;
  // for(int k=0; k<=l; k++)
  //   for(int j=0; j<=m; j++)
  //     array[0][j][k] = 0;

  for(int i=0; i<=n; i++)
    for(int j=0; j<=m; j++)
      for(int k=0; k<=l; k++){
        if(i == 0 || j == 0 || k == 0) array[i][j][k] = 0;
        else if(is_Equal(a[i-1], b[j-1], c[k-1])) array[i][j][k] = array[i-1][j-1][k-1] + 1;
        else array[i][j][k] = std::max(array[i-1][j][k], std::max(array[i][j-1][k], array[i][j][k-1]));
      }

  return array[n][m][l];
    // return std::min(std::min(a.size(), b.size()), c.size());
}

int main() {
  size_t an;
  std::cin >> an;
  vector<int> a(an);
  for (size_t i = 0; i < an; i++) {
    std::cin >> a[i];
  }
  size_t bn;
  std::cin >> bn;
  vector<int> b(bn);
  for (size_t i = 0; i < bn; i++) {
    std::cin >> b[i];
  }
  size_t cn;
  std::cin >> cn;
  vector<int> c(cn);
  for (size_t i = 0; i < cn; i++) {
    std::cin >> c[i];
  }
  std::cout << lcs3(a, b, c) << std::endl;
}
