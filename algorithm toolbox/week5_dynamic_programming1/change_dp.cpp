#include <iostream>
#include <algorithm>

using namespace std;

int get_change(int m) {
  //write your code here
	if(m <= 2) return m;
	else if(m <= 4) return 1;
	else{
		int change[m+1];

		//Base Cases
		change[0] = 0;
		change[1] = 1;
		change[2] = 2;
		change[3] = 1;
		change[4] = 1;

		//iterative step
		for(int i=5; i<=m; i++){
			change[i] = min(change[i-1], min(change[i-3],change[i-4])) + 1;
		}
		return change[m];
	}
}

int main() {
  int m;
  std::cin >> m;
  std::cout << get_change(m) << '\n';
}
