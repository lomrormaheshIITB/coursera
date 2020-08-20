#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <map>

using namespace std;

int main(){
	int n = 5000000;
	// cin >> n;
	srand(time(NULL));

	map<int, int>mymap;
	mymap.insert({0,65});
	mymap.insert({1,67});
	mymap.insert({2,71});
	mymap.insert({3,84});


	// cout << '$';
	for(int i=0; i<n; i++){
		int t = rand() % 4;
		char c = mymap.find(t)->second;
		if(i == 25)
			c = '$';
		cout << c;
	}

	return 0;
}