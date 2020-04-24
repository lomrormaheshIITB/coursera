#include <iostream>
#include <vector>
#include <numeric>

using std::vector;

bool subset(vector<int> &V, int n, int a, int b, int c){
	if(a == 0 && b == 0 && c == 0) return 1;
	if(n < 0) return 0;

	bool A = false;
	if(a >= V[n]){
		A = subset(V, n-1, a-V[n], b , c);
	}


	bool B = false;
	if(b >= V[n]){
		B = subset(V, n-1, a, b-V[n], c);
	}


	bool C = false;
	if(c >= V[n]){
		C = subset(V, n-1, a, b , c-V[n]);
	}

	return A || B || C;
}

int partition3(vector<int> &A) {
  //write your code here
	int n = A.size();

	if(n < 3) return 0;

	int sum = accumulate(A.begin(), A.end(), 0);
	
	if(sum % 3 != 0) return 0;

  return subset(A, n-1, sum/3, sum/3, sum/3);;
}

int main() {
  int n;
  std::cin >> n;
  vector<int> A(n);
  for (size_t i = 0; i < A.size(); ++i) {
    std::cin >> A[i];
  }
  std::cout << partition3(A) << '\n';
}
