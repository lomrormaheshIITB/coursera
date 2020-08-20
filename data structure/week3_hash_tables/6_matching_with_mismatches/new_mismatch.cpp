#include <iostream>
#include <vector>
#include <pair>

using std::vector;
using std::pair;
using namespace std;


// FIND NEXT MIS MATCH POSITION IN O(log n) time  // O(log p)
vector<int> next_mis_matches(vector<int>&hash1, vector<int>&hash_pattern, int start, int end, int pos, int p, vector<int>&xpow){
	vector<int>ans;

	// ***BASE CASE***
	// LENGTH = 1
	if( start == end ){
		if( hash1[start] != hash_pattern[start] ){
			ans.push_back(pos+start);
		}
		return ans;
	}

	// ***INDUCTION STEP***
	//LENGTH > 1
	int mid = (start+end)/2;
	if( hash1[mid] != hash_pattern[mid] ){
		vector<int>first = next_mis_matches(hash1, hash2, hash_pattern, start, mid, pos);
		ans.insert( ans.end(), first.begin(), first.end() );
	}
	int a = hash1[end] - hash1[mid]*xpow[mid];
	a = (a%p+p)%p; 
	int b = hash_pattern[end] - hash_pattern[mid]*xpow[mid];
	b = (b%p+p)%p; 
	
	if( a != b ){
		vector<int>second = next_mis_matches(hash1, hash2, hash_pattern, mid+1, end, pos);
		ans.insert( ans.end(), second.begin(), second.end() );
	}
	return ans;
}


vector<int> hash_func(const string &text, int prime, int x, int start, int l){
	vector<int>ans;

	int hash = 0;
	for(int i=start; i<l+start; i++){
		hash = hash*x + text[i];
		hash = hash % prime;
		ans.push_back(hash);
	}

	return ans;
}


vector<int> solve(int k, const string &text, const string &pattern) {
	vector<int> pos;
	int n = text.size();
	int m = pattern.size();

	int prime1;
	// int prime2;
	int x1;
	// int x2;

	// precompute x_powers 0 to m-1
	vector<int>xpower;
	int temp=1;
	for(int i=0; i<m; i++){
		xpower.push_back(temp);
		temp = temp * x1 % prime1;
	}

	// compute two hashes to decrease collision probability
	vector<vector<int> >hash1(n-m+1);
	// vector<vector<int> >hash2(n-m+1);

	// for every position find all hashes from length 1 to m
	for(int i=0; i<n-m+1; i++){
		hash1[i] = hash_func(text, prime1, x1, i, m);
		// hash2[i] = hash_func(text, prime2, x2, i, m);
	}

	int pos_text;
	int pos_pattern;
	int mismatch_num;

	for(int i=0; i<n-m+1; i++){
		mismatch_num = 0;
		pos_text = i;
		pos_pattern = 0;

		//FIND 'NUM OF MIS_MATCH' B/W 'I' AND 'I+W-1'
		for(int j=0; j<k+1; j++){
			next_mis_match(hash1[i], hash_pattern, 0, m-1, pos_text, prime, xpower);
			
		}

		// IF 'NUM OF MIS_MATCH > K' REJECT IT
	}

	return pos;
}

int main() {
	ios_base::sync_with_stdio(false), cin.tie(0);
	int k;
	string t, p;
	while (cin >> k >> t >> p) {
		auto a = solve(k, t, p);
		cout << a.size();
		for (int x : a)
			cout << " " << x;
		cout << "\n";
	}
}
