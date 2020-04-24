#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include <limits>
#include <algorithm>

using std::vector;
using std::string;
using std::max;
using std::min;

int INF = std::numeric_limits<int>::max();
int MINF = std::numeric_limits<int>::min();


int eval(int a, int b, char op) {
  if (op == '*') {
    return a * b;
  } else if (op == '+') {
    return a + b;
  } else if (op == '-') {
    return a - b;
  }else if (op == '/') {
    return a / b;
  } else {
    assert(0);
  }
}


int Parentheses(vector<int> &num, vector<char> &op, int n){
  
  // ***** PRINT NUMBERS AND OPERATORS *******
  // for(auto v=num.begin(); v!= num.end(); v++){
  //   std::cout<<*v<<" ";
  // }
  // std::cout<<"\n";

  // for(auto v=op.begin(); v!= op.end(); v++){
  //   std::cout<<*v<<" ";
  // }
  // std::cout<<"\n";
  // std::cout<<n<<"\n";

  //************************************************

  // std::cout<<"ENTER\n";
  vector<int>min_mat(n * n);
  vector<int>max_mat(n * n);
  
  for(int i=0; i<n; i++){
    min_mat[i * n + i] = num[i];
    max_mat[i * n + i] = num[i];
  }

  // std::cout<<"ENTER INTO LOOP\n";
  int a,b,c,d;
  int m, M;
  for(int s=1; s<=n-1; s++){
    for(int i=0; i<n-s; i++){
      //MinAndMax
      int j = i + s;
      m = INF;
      M = MINF;

      // std::cout<<"(" << i << ","<< j << ")\n";
      for(int k=i; k<j; k++){
        a = eval(max_mat[i*n+k], max_mat[(k+1)*n+j], op[k]);
        b = eval(max_mat[i*n+k], min_mat[(k+1)*n+j], op[k]);
        c = eval(min_mat[i*n+k], max_mat[(k+1)*n+j], op[k]);
        d = eval(min_mat[i*n+k], min_mat[(k+1)*n+j], op[k]);
        m = min(m ,min(a, min(b, min(c, d))));
        M = max(M, max(a, max(b, max(c, d))));
        // std::cout<<a <<" "<< b <<" "<< c <<" "<< d << "\n";
      }
        // std::cout<<"m="<<m<<" M="<<M;
        // std::cout<<"\n---------------------------------------------\n";

      min_mat[i * n + j] = m;
      max_mat[i * n + j] = M;
    }
    // break;
  }

  // ------------------- PRINTING MAX MIN ---------------------------------
  // std::cout<<"\n--------------------------------------------------\n";

  // for(int i=0; i<n; i++){
  //   for(int j=0; j<n; j++){
  //     if(i>j) std::cout<<"  \t";
  //     else std::cout<<max_mat[i*n+j]<<"\t";
  //   }
  //   std::cout<<"\n";
  // }
  //   std::cout<<"\n--------------------------------------------------\n";

  // for(int i=0; i<n; i++){
  //   for(int j=0; j<n; j++){
  //     if(i>j) std::cout<<"  \t";
  //     else std::cout<<min_mat[i*n+j]<<"\t";
  //   }
  //   std::cout<<"\n";
  // }
  //   std::cout<<"\n--------------------------------------------------\n";



  return max_mat[0*n + n-1];
}


int get_maximum_value(const string &exp) {
  //write your code here
  vector<int> Operands;
  vector<char> Operator;
  int total_nums = 1;

  int i = 0;
  string number = "";
  while(i != exp.size()){
    if(exp[i] == '*' || exp[i] == '+' || exp[i] == '-'){
      Operands.push_back(stoi(number));
      Operator.push_back(exp[i]);
      number = "";
      total_nums++;
    }
    else{
      number += exp[i];
    }
    i++;
  }
  Operands.push_back(stoi(number));

  if(total_nums == 1) return stoi(number);

  return Parentheses(Operands, Operator, total_nums);
}

int main() {
  string s;
  std::cin >> s;
  std::cout << get_maximum_value(s) << '\n';
}
