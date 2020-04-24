#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;
using std::max;

void max_sliding_window_naive(vector<int> const & A, int w) {
    for (size_t i = 0; i < A.size() - w + 1; ++i) {
        int window_max = A.at(i);
        for (size_t j = i + 1; j < i + w; ++j)
            window_max = max(window_max, A.at(j));

        cout << window_max << " ";
    }

    return;
}


void fast_algo(vector<int> const & A, int w) {
    int index;
    int maxi = -1;
    for(int i=0; i<w; i++){
        if(A[i] > maxi){
            index = i;
            maxi = std::max(A[i], maxi);
        } 
    }
    vector<int> output;
    output.push_back(maxi);

    for(int i=w; i<n; i++){
        
    }
}

int main() {
    int n = 0;
    cin >> n;

    vector<int> A(n);
    for (size_t i = 0; i < n; ++i)
        cin >> A.at(i);

    int w = 0;
    cin >> w;

    max_sliding_window_naive(A, w);

    return 0;
}
