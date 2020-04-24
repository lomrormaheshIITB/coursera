#include <algorithm>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>

using std::vector;
using std::string;

bool helper(string a, string b){

  if(a == "") return false;
  if(b == "") return true;
  int alen = a.size();
  int blen = b.size();

  int m;
  if(alen < blen) m = alen;
  else m = blen;

  for(int i=0; i<m; i++){
    int a1 = (int)a[i];
    int b1 = (int)b[i];

    if(a1 > b1) return true;
    if(b1 > a1) return false;
  }

  if(alen == blen) return true;
  else{
    if(alen == m) return helper(a, b.substr(m, blen-m));
    else return helper(a.substr(m, alen - m), b);
  }

}
string largest_number(vector<string> a) {
  //write your code here
  string answer = "";

  int included[a.size()];

  for(int i=0; i<a.size(); i++){
    included[i] = 0;
  }

  for (int i = 0; i < a.size(); ++i)
  {
    /* code */
    string max = "";
    for(int j=0; j < a.size(); j++){
      if(!included[j] and max == "") max = a[j];
      else if(!included[j] and helper(a[j], max)) max = a[j];
    }

    if(max == "") break;
    else{
      for( int j=0; j < a.size(); j++)
        if(!included[j] and max == a[j]){
          included[j] = 1; break;
        }
    }
    // std::cout << max << "\n";
    answer = answer + max;
  }

  return answer;
}

int main() {
  int n;
  std::cin >> n;
  vector<string> a(n);
  for (size_t i = 0; i < a.size(); i++) {
    std::cin >> a[i];
  }
  std::cout << largest_number(a);
}
