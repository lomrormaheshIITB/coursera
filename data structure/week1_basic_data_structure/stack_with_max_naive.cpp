#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <algorithm>

using std::cin;
using std::string;
using std::vector;
using std::cout;
using std::max_element;

class StackWithMax {
    vector<int> stack;
    vector<int> stack_max;
    int maxi = -1;

  public:

    void Push(int value) {
        stack.push_back(value);
        maxi = std::max(maxi, value);
        stack_max.push_back(maxi);
    }

    void Pop() {
        assert(stack.size());
        stack.pop_back();
        stack_max.pop_back();
        maxi = *(stack_max.end()-1);
    }

    int Max() const {
        assert(stack.size());
        return maxi;
        return *max_element(stack.begin(), stack.end());
    }
};

int main() {
    int num_queries = 0;
    cin >> num_queries;

    string query;
    string value;

    StackWithMax stack;

    for (int i = 0; i < num_queries; ++i) {
        cin >> query;
        if (query == "push") {
            cin >> value;
            stack.Push(std::stoi(value));
        }
        else if (query == "pop") {
            stack.Pop();
        }
        else if (query == "max") {
            cout << stack.Max() << "\n";
        }
        else {
            assert(0);
        }
    }
    return 0;
}