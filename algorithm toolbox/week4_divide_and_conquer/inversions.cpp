#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cassert>

using std::vector;

long long merge(vector<int> &a, vector<int> &b, size_t left, size_t mid, size_t right){
	// std::cout<<"-------------- ENTER -------\n";
	size_t i = left;
	size_t j = mid+1;
	size_t t = left;

	long long number_of_inversions = 0;

	// copy a into b (only required part)
	for(size_t x=left; x<= right; x++){
		b[x] = a[x];
	}

	//used while merging to get num_conersions
	bool first_time = true;
	bool i_inc = false;

	while(i <= mid and j <= right){
		if(b[i] <= b[j]){
			a[t] = b[i];
			t++;
			
			first_time = true;
			if(i_inc){
				// std::cout<<b[i]<<" "<<b[j-1]<<"\n";
				if(b[i] > b[j-1]) {
					number_of_inversions += j-1-mid;
					// std::cout<<"3333333333333333333333333\n";
				}
			}
			i++;
			i_inc = true;
		}
		// else if(b[i] == b[j]){
		// 	a[t] = b[i];
		// 	t++;
		// 	i++;
		// 	first_time = true;
		// 	number_of_inversions += (j-mid-1);
		// 	std::cout<<" == "<<(j-mid-1)<<"\n";
		// }
		else if(b[i] > b[j]){
			a[t] = b[j];
			t++;
			i_inc = false;
			if(first_time){
				first_time = false;
				number_of_inversions += j - mid;
				// std::cout<<j - mid<<"\n";	
				j++;
			}else{
				number_of_inversions += 1;
				j++;
			}
		}		
	}

	if(i <= mid){
		number_of_inversions += (mid-i)*(right - mid);
		// std::cout<<"=========== "<<(mid-i)*(right - mid)<<"\n";
		while(i <= mid){
			a[t] = b[i];
			t++;
			i++;
		}
	}
	else if(j <= right){
		while( j<= right ){
			a[t] = b[j];
			t++;
			j++;
		}
	}

	// std::cout<<number_of_inversions<<"\n";
	// std::cout<<left<<" "<<mid<<" "<<right<<"\n";
	return number_of_inversions;
}


long long mergesort(vector<int> &a, vector<int> &b, size_t left, size_t right){
	// std::cout << "entered\n";
	long long number_of_inversions = 0;

	// Base Cases:
	//(1) just one number
	if(1 + left > right) return 0;
	//(2) two numbers
	else if(left + 1 == right){
		if(a[left] <= a[right]) return 0;
		else {
			int temp = a[left];
			a[left] = a[right];
			a[right] = temp;
			// std::cout<<"----------------\n";
			return 1;
		}
	}

	size_t mid = (left + right) / 2;
	number_of_inversions += mergesort(a, b, left, mid);
	number_of_inversions += mergesort(a, b, mid+1, right);

	number_of_inversions += merge(a, b, left, mid, right);

	return number_of_inversions;
  
}

long long get_number_of_inversions(vector<int> &a, vector<int> &b, size_t left, size_t right) {


  	// right is included
  	// for(size_t i=left; i<right; i++)
  	// 	std::cout<<a[i]<<" ";
  	// std::cout<<std::endl;
  	return mergesort(a, b,left, right-1);
}


long long naive(vector<int> &a, vector<int> &b, size_t left, size_t right){
	long long number_of_inversions = 0;
	for(int i=0; i<right; i++)
		for(int j=i+1; j<right; j++)
			if(a[i] > a[j]) number_of_inversions++;

	return number_of_inversions;
}

void test_solution(){
	size_t n = rand() % 10000;
	// n = n % 10000;

	vector<int>a(n);
	vector<int>b(n);
	for(size_t i=0; i<n; i++){
		a[i] = rand() % 1000000000;
		// a[i] = a[i] % 1000000000;
	}
	std::cout<<"naive="<<naive(a,b,0,n)<<"\n";
	std::cout<<"fast ="<<get_number_of_inversions(a,b,0,n)<<"\n";
	// if(0 != 0){
	// 	std::cout<<"=======================\n";
	// }
	if(naive(a,b,0,n) - get_number_of_inversions(a,b,0,n) != 0){
		std::cout<<n<<"\n";
		for(size_t i=0; i<n; i++){
			std::cout<<a[i]<<" ";
		}
		std::cout<<"\n";
	}
	assert(naive(a,b,0,n) == get_number_of_inversions(a,b,0,n));
	return;
}


int main() {
	int n;
	std::cin >> n;
	vector<int> a(n);
	for (size_t i = 0; i < a.size(); i++) {
	std::cin >> a[i];
	}
	vector<int> b(a.size());
	// for(int i=0; i<1000; i++)	test_solution();
	std::cout << get_number_of_inversions(a, b, 0, a.size()) << '\n';
}
