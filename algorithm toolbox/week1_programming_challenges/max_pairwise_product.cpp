#include <iostream>
#include <vector>
#include <algorithm>

long long MaxPairwiseProduct(const std::vector<int>& numbers) {
    long long max_product = 0;
    int n = numbers.size();

/*    for (int first = 0; first < n; ++first) {
        for (int second = first + 1; second < n; ++second) {
            max_product = std::max(max_product,
                numbers[first] * numbers[second]);
        }
    } */

    int index1 = -1;
    int index2 = -1;

    for(int i=0; i<n; ++i){
        if(numbers[i] > numbers[index1]){ index2=index1; index1 = i;}
        else{
            if(numbers[i] > numbers[index2]){index2=i;}
        }
    }

    max_product = (long long)numbers[index1] * numbers[index2];

    return max_product;
}

int main() {
    int n;
    std::cin >> n;
    std::vector<int> numbers(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> numbers[i];
    }

    std::cout << MaxPairwiseProduct(numbers) << "\n";
    return 0;
}
