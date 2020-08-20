#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>

using namespace std;

int main(){
	int n;
	cin >> n;
	srand(time(NULL));

	cout << n <<endl;
	for(int i=0; i<n; i++)
		cout <<  rand() % 10000 - 5698 << " ";
}