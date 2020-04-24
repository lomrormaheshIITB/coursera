#include <iostream>
#include <algorithm>
#include <vector>

using std::vector;
using std::min;
using namespace std;

struct Answer {
	size_t i, j, len;
};

int ascii(char c){
	return (int)c;
}

int func_hash(const string &s, int p, int x){
	// std::cout<<"ENTER HASH...\n";
	// p = prime , x = multiplier
	int n = s.size();
	int h=0;
	for(int i=n-1; i>=0; i--){
		h = (h*x + ascii(s[i]))%p;
	}

	return h;
}


vector<int> helper(const string &s, int p, int x, int k){
	// std::cout<<"ENTER HELPER...\n";
	// p = prime , x = multiplier, k = substr len
	int n = s.size();
	vector<int>ans(n-k+1, -1);

	// COMPUTE LAST TERM
	ans[n-k]=func_hash(s.substr(n-k,k), p, x);

	// CACULATE x^k%p
	int y=1;
	for(int i=0; i<k; i++)
		y = y*x%p;

	// COMPUTING REST OF TERMS(1..n-k+1)ths
	for(int i=n-k-1; i>=0; i--){
		ans[i] = (ans[i+1]*x + ascii(s[i]) - ascii(s[i+k])*y)%p;
		ans[i] = (ans[i] + p)%p;
	}

	return ans;

}


Answer solve(const string &s, const string &t) {
	// std::cout <<"ENTER...\n";
	Answer ans = {0, 0, 0};
	int p1 = 1000033;
	int p2 = 1000037;
	int x1 = 3;
	int x2 = 7;
	int n = s.size(); // length of s
	int m = t.size(); // length of t
	int max_pos_len = min(n,m);
	// std::cout<<"S=" << n << "          T="<<m<<"\n";

	bool found = false;
	for(int i=1; i<=max_pos_len; i++){
		found = false;
		vector<int>sfunc_hash1 = helper(s, p1, x1, i);
		vector<int>sfunc_hash2 = helper(s, p2, x2, i);
		vector<int>tfunc_hash1 = helper(t, p1, x1, i);
		vector<int>tfunc_hash2 = helper(t, p2, x2, i);

		for(int j=0; j<sfunc_hash1.size(); j++){
			for(int k=0; k<tfunc_hash1.size(); k++){
					// BREAKPOINT
					// std::cout << s.substr(j, i) << " " << t.substr(k, i) << "\n";
					// if(s.substr(j, i) == t.substr(k, i)){
					// 	std::cout<< sfunc_hash1[j] << " " << tfunc_hash1[k] << "\n";
					// 	return ans;
					// }
				if(sfunc_hash1[j] == tfunc_hash1[k] and sfunc_hash2[j] == tfunc_hash2[k]){
					ans.i = j;
					ans.j = k;
					ans .len = i;
					// return ans;
					found = true;
					break;
				}
			}
			if(found) break;
		}
		if(!found) return ans;
	}

	return ans;
}

int main() {
	ios_base::sync_with_stdio(false), cin.tie(0);
	string s, t;
	while (cin >> s >> t) {
		auto ans = solve(s, t);
		cout << ans.i << " " << ans.j << " " << ans.len << "\n";
	}
}
