#include <iostream>
#include <cassert>

// int fibonacci_sum_squares_naive(long long n) {
//     if (n <= 1)
//         return n;

//     long long previous = 0;
//     long long current  = 1;
//     long long sum      = 1;

//     for (long long i = 0; i < n - 1; ++i) {
//         long long tmp_previous = previous;
//         previous = current;
//         current = tmp_previous + current;
//         sum += current * current;
//     }

//     std::cout << sum << "\n";
//     return sum % 10;
// }

int fibonacci_sum_squares_naive(long long n) {
    if (n <= 1)
        return n;

    long long previous = 0;
    long long current  = 1;
    long long sum      = 1;

    for (long long i = 0; i < n - 1; ++i) {
        long long tmp_previous = previous;
        previous = current;
        current = tmp_previous + current;
        sum += current * current;
        sum = sum % 100;
    }

    // std::cout << sum << "\n";
    return sum % 10;
}

// int fast(long long n){
//     if (n <= 1)
//         return n;

//     long long previous = 0;
//     long long current  = 1;
//     long long sum;

//     long long summation = 0;

//     for (long long i = 0; i < n - 1; ++i) {
//         long long tmp_previous = previous;
//         previous = current;
//         current = tmp_previous + current;
//         summation += current*previous;
//         current = current % 100;
//         summation = summation % 100;
//     }

//     summation = summation - current*previous;
//     sum = 2*current*current + previous*previous - 1 - 2*summation;
//     // std::cout << sum << "\n";
//     return (int) (sum % 10);
// }

// void test_solutuin(){
//     for(long long i=5; i<100; i++){
//         std::cout << i << "\n";
//         assert(fibonacci_sum_squares_naive(i) == fast(i));
//     }
// }

int main() {
    long long n = 0;
    std::cin >> n;
    std::cout << fibonacci_sum_squares_naive(n) << "\n";
    // test_solutuin();
    // std::cout << fast(n) << "\n";
}
