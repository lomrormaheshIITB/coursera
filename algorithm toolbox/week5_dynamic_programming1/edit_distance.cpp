#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

using std::string;

int diff(char a, char b){
	if(a == b) return 0;
	return 1;
}

int edit_distance(const string &str1, const string &str2) {
  //write your code here
	int l1 = str1.size();
	int l2 = str2.size();

	int ed[l1+1][l2+1];
	for(int i=0; i<=l1; i++) ed[i][0] = i;
	for(int j=0; j<=l2; j++) ed[0][j] = j;

	for(int i=1; i<=l1; i++)
		for(int j=1; j<=l2; j++)
			ed[i][j] = min(min(ed[i][j-1], ed[i-1][j]) + 1, ed[i-1][j-1] + diff(str1[i-1], str2[j-1]));

	// for(int i=0; i<=l1; i++){
	// 	for(int j=0; j<=l2; j++)
	// 		std::cout<<ed[i][j]<<" ";
	// 	std::cout<<"\n";
	// }
	return ed[l1][l2];
	// std::cout<<diff(str1[0], str2[0])<<"\n";
}

int main() {
  string str1;
  string str2;
  std::cin >> str1 >> str2;
  std::cout << edit_distance(str1, str2) << std::endl;
  return 0;
}
