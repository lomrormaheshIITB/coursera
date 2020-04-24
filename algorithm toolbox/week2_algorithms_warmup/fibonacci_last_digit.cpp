#include <iostream>
// #include <cassert>

int get_fibonacci_last_digit_naive(int n) {
    if (n <= 1)
        return n;

    int previous = 0;
    int current  = 1;

    for (int i = 0; i < n - 1; ++i) {
        int tmp_previous = previous;
        previous = current;
        current = tmp_previous + current;
    }

    return current % 10;
}

long long get_fast_fibonacci_last_digit(int n) {
    // write your code here
    long long store[n+1];
    store[0] = 0;
    store[1] = 1;

    int previous = 0;
    int current = 1;

    for(int i=2; i<n+1; i++){
        int temp = previous;
        previous = current;
        current = temp + current;
        current = current % 100;
    }

    return current%10;
}

// void test_solution() {
//     assert(get_fast_fibonacci_last_digit(3) == 2);
//     assert(get_fast_fibonacci_last_digit(10) == 5);
//     for (int n = 0; n < 20; ++n)
//         assert(get_fast_fibonacci_last_digit(n) == get_fibonacci_last_digit_naive(n));
// }

int main() {
    int n;
    std::cin >> n;
    // int cd = get_fibonacci_last_digit_naive(n);
    // std::cout << cd << '\n';
    // test_solution();
    int c = get_fast_fibonacci_last_digit(n);
    std::cout << c << '\n';
    }
