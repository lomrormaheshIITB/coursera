#include <iostream>
#include <vector>
#include <math.h>

using std::vector;
using namespace std;

class Solver {
	string s;
	vector<long long>h1;
	vector<long long>h2;
	vector<long>x_pow_m1;
	vector<long>x_pow_m2;
	long  m1;
	long  m2;
	int T;
	long  x = 11;

	int ascii(char c){
		return (int)c;
	}

public:	
	Solver(string s) : s(s) {	
		// initialization, precalculation
		m1 = 1000000000 + 7;
		m2 = 1000000000 + 9;
		T = s.size();
		h1.resize(T+1);
		h2.resize(T+1);
		x_pow_m1.resize(T+1);
		x_pow_m2.resize(T+1);
		h1[0] = 0;
		h2[0] = 0;
		x_pow_m1[0] = 1;
		x_pow_m2[0] = 1;
		for(int i=1; i<=T; i++){
			// h1[i] = (x*h1[i-1] + ascii(s[i-1])) % m1;
			h1[i] = fmod(x*h1[i-1] + ascii(s[i-1]), m1);
			// h2[i] = (x*h2[i-1] + ascii(s[i-1])) % m2;
			h2[i] = fmod(x*h2[i-1] + ascii(s[i-1]), m2);
			x_pow_m1[i] = fmod(x_pow_m1[i-1]*x , m1);
			x_pow_m2[i] = fmod(x_pow_m2[i-1]*x , m2);
		}
	}

	bool ask(int a, int b, int l) {

		long  aa = h1[a+l] - h1[a]*x_pow_m1[l];
		aa = fmod(aa, m1);
		aa = fmod(aa+m1, m1);

		long  bb = h1[b+l] - h1[b]*x_pow_m1[l];
		bb = fmod(bb, m1);
		bb = fmod(bb+m1, m1);

		long  cc = h2[a+l] - h2[a]*x_pow_m2[l];
		cc = fmod(cc, m2); 
		cc = fmod(cc+m2, m2);

		long  dd = h2[b+l] - h2[b]*x_pow_m2[l];
		dd = fmod(dd, m2);
		dd = fmod(dd+m2, m2);

		// std::cout<<aa <<" " << bb <<" " << cc <<" " << dd << "\n";
		bool my = (aa == bb and cc == dd);
		// bool expected = s.substr(a, l) == s.substr(b, l);
		// if(my != expected){
		// 	std::cout<<"WRONG:" << a <<" "<< b <<" "<< l << "\n";
		// // }
		if(my)
			if(s.substr(a, l) == s.substr(b, l))
				return true;
		return false;
		return s.substr(a, l) == s.substr(b, l);
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
