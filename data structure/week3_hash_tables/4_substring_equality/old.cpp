#include <iostream>
#include <vector>
#include <math.h>

using std::vector;
using namespace std;

class Solver {
	string s;
	vector<long>hash1;
	vector<long>hash2;
	vector<long>x_pow_p1;
	vector<long>x_pow_p2;
	long  p1;
	long  p2;
	long  x1;
	long  x2;
	int n;

	int ascii(char c){
		return (int)c;
	}

	long modula(long a, long b){
		return fmod(fmod(a,b)+b, b);
	}

public:	
	Solver(string s) : s(s) {	
		//-----------------------
		p1 = 1000033;
		p2 = 1000037;
		x1 = 3;
		x2 = 7;
		//-----------------------
		// initialization, precalculation
		p1 = 1000000000 + 7;
		p2 = 1000000000 + 9;
		n = s.size();
		hash1.resize(n);
		hash2.resize(n);
		x_pow_p1.resize(n); 
		x_pow_p2.resize(n); // x^1 x^2 .....

		long temp1 = 0;
		long temp2 = 0;
		long temp3 = 1;
		long temp4 = 1;
		for(int i=0; i<n; i++){
			temp1 = (temp1*x1 + ascii(s[i]))%p1;
			hash1[i]=temp1;
			temp2 = (temp2*x2 + ascii(s[i]))%p2;
			hash2[i]=temp2;

			temp3 = temp3*x1 % p1;
			x_pow_p1[i]=temp3;
			temp4 = temp4*x2 % p2;
			x_pow_p2[i]=temp4;
		}
	}

	bool ask(int a, int b, int l) {

		long  temp1 = modula(hash1[a+l-1] - hash1[a-1] * x_pow_p1[l-1], p1);
		long  temp2 = modula(hash1[b+l-1] - hash1[b-1] * x_pow_p1[l-1], p1);

		long  temp3 = modula(hash2[a+l-1] - hash2[a-1] * x_pow_p2[l-1], p2);
		long  temp4 = modula(hash2[b+l-1] - hash2[b-1] * x_pow_p2[l-1], p2);

		return temp1 == temp2 and temp3 == temp4;

	}
};

int main() {
	ios_base::sync_with_stdio(0), cin.tie(0);

	string s;
	int q;
	cin >> s >> q;
	Solver solver(s);
	for (int i = 0; i < q; i++) {
		int a, b, l;
		cin >> a >> b >> l;
		cout << (solver.ask(a, b, l) ? "Yes\n" : "No\n");
	}
}
