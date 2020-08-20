#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <map>

using namespace std;

int main(){
	int n = 1000000;
	int m = 5000; // number of testcases
	// cin >> n;
	srand(time(NULL));

	map<int, int>mymap;
	mymap.insert({0,65});
	mymap.insert({1,67});
	mymap.insert({2,71});
	mymap.insert({3,84});


	int pos = rand() % 52 + 5;
	for(int i=0; i<n; i++){
		int t = rand() % 4;
		char c = mymap.find(t)->second;
		if(i == pos)
			c = '$';
		cout << c;
	}

	cout << endl;

	cout << m << endl;

	for(int i=0; i<m; i++){
		int k = rand() % 1000 + 3 ;
		for(int i=0; i<k; i++){
			int t = rand() % 4;
			char c = mymap.find(t)->second;
			cout << c;
		}
		cout << " ";
	}

	return 0;
}