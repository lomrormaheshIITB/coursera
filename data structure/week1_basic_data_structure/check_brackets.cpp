#include <iostream>
#include <stack>
#include <string>

struct Bracket {
    Bracket(char type, int position):
        type(type),
        position(position)
    {}

    bool Matchc(char c) {
        if (type == '[' && c == ']')
            return true;
        if (type == '{' && c == '}')
            return true;
        if (type == '(' && c == ')')
            return true;
        return false;
    }

    char type;
    int position;
};

bool check(char last, char next){
    if (last == '[' && next == ']')
        return true;
    if (last == '{' && next == '}')
        return true;
    if (last == '(' && next == ')')
       return true;
    return false;
}


int main() {
    std::string text;
    getline(std::cin, text);

    std::stack <Bracket> opening_brackets_stack;

    for (int position = 0; position < text.length(); ++position) {
        char next = text[position];

        if (next == '(' || next == '[' || next == '{') {
            // Process opening bracket, write your code here
            Bracket b(next, position);
            opening_brackets_stack.push(b);
        }
        if (next == ')' || next == ']' || next == '}') {
            // Process closing bracket, write your code here
            if(opening_brackets_stack.empty()){
                std::cout<<position+1<<"\n";
                return 0;
                break;
            }
            if(opening_brackets_stack.top().Matchc(next)){
                opening_brackets_stack.pop();
            }
            else{
                std::cout<<position+1<<"\n";
                return 0;
                break;
            }

        }
    }

    // Printing answer, write your code here
    if(opening_brackets_stack.empty()){
        std::cout<<"Success\n";
    }
    else{
        std::cout<<opening_brackets_stack.top().position +1<<"\n";
    }

    return 0;
}


// int main() {
//     std::string text;
//     getline(std::cin, text);

//     std::stack <Bracket> opening_brackets_stack;

//     std::stack<char> brac;
//     std::stack<int> pos;
//     for (int position = 0; position < text.length(); ++position) {
//         char next = text[position];

//         if (next == '(' || next == '[' || next == '{') {
//             // Process opening bracket, write your code here
//             brac.push(next);
//             pos.push(position);
//         }

//         if (next == ')' || next == ']' || next == '}') {
//             // Process closing bracket, write your code here
//             if(brac.empty()){
//                 std::cout<<position+1<<"\n";
//                 return 0;
//                 break;
//             }
//             char last = brac.top();
//             if(!check(last, next)){
//                 std::cout<<position+1<<"\n";
//                 return 0;
//                 break;
//             }
//             else{
//                 brac.pop();
//                 pos.pop();
//             }
//         }
//     }

//     // Printing answer, write your code here
//     if(brac.empty()) std::cout<<"Success\n";
//     else std::cout<<pos.top()+1<<"\n";

//     return 0;
// }
