#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;
typedef unsigned long long ull;

struct Data {
    string pattern, text;
};

Data read_input() {
    Data data;
    std::cin >> data.pattern >> data.text;
    return data;
}

void print_occurrences(const std::vector<int>& output) {
    for (size_t i = 0; i < output.size(); ++i)
        std::cout << output[i] << " ";
    std::cout << "\n";
}

// ASCII VALUE
int ascii(char c){
	return (int)c;
}
	
//POLYHASH
unsigned long long PolyHash(const string& s, unsigned long long x, unsigned long long p){
    unsigned long long hash = 0;
    for (int i = s.size()-1; i >= 0; i--)
        hash = ( hash * x + ascii(s[i]) ) % p;
    return hash;
}


std::vector<int> get_occurrences(const Data& input) {
    const string& s = input.pattern, t = input.text;
    std::vector<int> ans;
    long T = t.size();
    long P = s.size();

    // unsigned long long p = 11; // prime
    unsigned long long p = 5000011; // prime
	unsigned long long x = 37;  // multiplier

	// PreComputeHashes
	vector<unsigned long long>hash_map(T-P+1);

	hash_map[T-P] = PolyHash(t.substr(T-P, P), x, p);

    unsigned long long y = 1;
    for(long i=0; i<P; i++) {
    	y = (y*x) % p;
    }

    for(long i=T-P-1; i>=0; i--){
    	hash_map[i] = (p + hash_map[i+1]*x%p + ascii(t[i])%p - y*ascii(t[i+P])%p ) % p; 
    }

    // CHECK MATCH
    unsigned long long test_hash = PolyHash(s, x, p);
    for(int i=0; i + P <= T; i++){      
    	if(hash_map[i] == test_hash){
    		if(s == t.substr(i,P)){
    			ans.push_back(i);
    		}
    	}
    }

    return ans;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    print_occurrences(get_occurrences(read_input()));
    return 0;
}
