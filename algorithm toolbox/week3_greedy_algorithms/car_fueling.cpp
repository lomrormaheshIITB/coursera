#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;
using std::max;

int compute_min_refills(int dist, int tank, vector<int> & stops) {
    // write your code here
    int num_refill = 0;
    int fuel = tank - stops[0];

    // can't reach first stop or last destination from last stop 
    if(fuel < 0) return -1;
    if(tank + stops[stops.size()-1] < dist) return -1;

    for(int i=0; i<stops.size() -1; i++){
        int rel_dist = stops[i+1] - stops[i];
        if(rel_dist > tank) return -1;

        if(fuel - rel_dist >= 0) {fuel = fuel - rel_dist;}
        else{
            num_refill++;
            fuel = tank - rel_dist;
        }
    }

    if(fuel + stops[stops.size()-1] < dist) num_refill++;
    return num_refill;
}


int main() {
    int d = 0;
    cin >> d;
    int m = 0;
    cin >> m;
    int n = 0;
    cin >> n;

    vector<int> stops(n);
    for (size_t i = 0; i < n; ++i)
        cin >> stops.at(i);

    cout << compute_min_refills(d, m, stops) << "\n";

    return 0;
}
