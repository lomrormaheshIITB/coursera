#include <iostream>
#include <cassert>

int fibonacci_sum_naive(long long n) {
    if (n <= 1)
        return n;

    long long previous = 0;
    long long current  = 1;
    long long sum      = 1;

    for (long long i = 0; i < n - 1; ++i) {
        if(i%1000000000 == 0) std:: cout << "i = " << i << std::endl;
        long long tmp_previous = previous;
        previous = current;
        current = tmp_previous + current;
        sum += current;
        current = current % 100;
        sum = sum % 100;
    }

    return sum % 10;
}

// int fast_fibonacci_sum(long long n) {
//     if (n <= 1)
//         return n;

//     long long previous = 0;
//     long long current  = 1;
//     long long sum      = 1;

//     for (long long i = 0; i < n - 1; ++i) {
//         long long tmp_previous = previous;
//         previous = current;
//         current = tmp_previous + current;
//         current = current % 100;
//     }

//     // std::cout << sum << std::endl;
//     sum = 2*current + previous - 1;
//     // std::cout << sum << std::endl;
//     return sum % 10; 
// }

// void test_solutuin(){
//     for(long long i=5698356; i<5698400; i++){
//         assert(fibonacci_sum_naive(i+56985698) == fast_fibonacci_sum(i+56985698));
//     }
// }

int main() {
    long long n = 0;
    std::cin >> n;
    std::cout << fibonacci_sum_naive(n) << std::endl;
    // test_solutuin();

    // std::cout << fast_fibonacci_sum(n) << std::endl;
}
