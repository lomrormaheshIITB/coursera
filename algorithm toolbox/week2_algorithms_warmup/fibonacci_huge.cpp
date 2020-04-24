#include <iostream>
// #include <cassert>

long long get_fibonacci_huge_naive(long long n, long long m) {
    if (n <= 1)
        return n;

    long long previous = 0;
    long long current  = 1;

    for (long long i = 0; i < n - 1; ++i) {
        long long tmp_previous = previous;
        previous = current;
        current = tmp_previous + current;
    }

    return current % m;
}

long long get_fast_fibonacci_huge(long long n, long long m){
    if (n <= 1)
        return n;

    long long previous = 0;
    long long current  = 1;

    for (long long i = 0; i < n - 1; ++i) {
        long long tmp_previous = previous;
        previous = current;
        current = tmp_previous + current;
        current = current % 2*m;
    }

    return current % m;
}

// void test_solutuin(){
//     for(int i=3; i<20; i++){
//         assert((get_fibonacci_huge_naive(i,20000) - get_fast_fibonacci_huge(i,20000)) == 0);
//     }
// }

int main() {
    long long n, m;
    std::cin >> n >> m;
    // std::cout << get_fibonacci_huge_naive(n, m) << '\n';
    // test_solutuin();
    std::cout << get_fast_fibonacci_huge(n, m) << '\n';
}
