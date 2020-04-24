#include <iostream>
#include <vector>
#include <cassert>
using std::vector;

long long get_fibonacci_partial_sum_naive(long long from, long long to) {
    long long sum = 0;

    long long current = 0;
    long long next  = 1;

    for (long long i = 0; i <= to; ++i) {
        if (i >= from) {
            sum += current;
            sum = sum % 100;
        }

        long long new_current = next;
        next = next + current;
        current = new_current;
    }

    // std::cout << sum << "\n";
    return sum % 10;
}

// long long fast(long long m, long long n){
//     long long previous = 0;
//     long long current  = 1;
//     long long sum = 0;

//     for(long long i=2; i<= m+1; i++){
//         long long tmp_previous = previous;
//         previous = current;
//         current = tmp_previous + current;
//     }

//     long long m1th = current;

//     for(long long i=m+2; i<= n; i++){
//         long long tmp_previous = previous;
//         previous = current;
//         current = tmp_previous + current;
//     }

//     sum = 2*current + previous - m1th;
//     // std::cout << sum << "\n";
    
//     if(n-m == 1){
//         return (((current + previous) % 10) + 10) % 10;
//     }
//     if(m==n && n > 1){
//         return ((current % 10) + 10) % 10;
//     }
//     if(m == n and n == 0){
//         return n;
//     }
//     return (sum % 10 + 10) % 10;
// }

// void test_solutuin(){
//     for(long long i=5; i<20; i++){
//         assert(get_fibonacci_partial_sum_naive(i, 2*i-3) == fast(i,2*i-3));
//     }
// }

int main() {
    long long from, to;
    std::cin >> from >> to;
    std::cout << get_fibonacci_partial_sum_naive(from, to) << '\n';
    // test_solutuin();
    // std::cout << fast(from, to) << '\n';
}
