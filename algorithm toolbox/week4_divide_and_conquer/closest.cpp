#include <algorithm>
#include <cassert>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <string>
#include <cmath>
#include <limits>

using std::vector;
using std::string;
using std::pair;
using std::min;

double INF = std::numeric_limits<double>::max();


bool sortcol(const vector<int>& v1, const vector<int>& v2){
		return v1[0] < v2[0];
	}

bool sortrow(const vector<int>& v1, const vector<int>& v2){
		return v1[1] < v2[1];
	}

double euclidean_distance(int x1, int y1, int x2, int y2){
	return sqrt(pow(x1-x2,2) + pow(y1-y2,2));
}

double helper(vector<int> x, vector<int> y, int low, int high) {
	// std::cout<<"low = " <<low<<" high = "<<high << " -------\n";
	// base case (0, 1 points)
	if(high - low < 1) return INF;
	// base cases (2, 3 points)
	if(high - low == 1){
		// std::cout << euclidean_distance(x[low], y[low], x[high], y[high]) << " -------\n";
		return euclidean_distance(x[low], y[low], x[high], y[high]);
	}
	if(high - low == 2){
		double d1 = euclidean_distance(x[low], y[low], x[high], y[high]);
		double d2 = euclidean_distance(x[low], y[low], x[low+1], y[low+1]);
		double d3 = euclidean_distance(x[low+1], y[low+1], x[high], y[high]);
		// std::cout<< min(d1, min(d2, d3)) << " -----------\n";

		return min(d1, min(d2, d3));
	}
	


	// divide rule
	int mid = low + (high - low) / 2;
	double d1 = helper(x, y, low, mid);
	double d2 = helper(x, y, mid+1, high);

	double d = min(d1, d2);

	//if two coincide points
	if( d  == 0) return d;

	//points in the strip d in S1, S2   
	double strip_low = (x[mid] + x[mid+1]) / 2 - d; 
	double strip_high = (x[mid] + x[mid+1]) / 2 + d;

	// std::cout<<"low = " <<low<<" high = "<<high <<std::endl;
	// std::cout<<strip_low <<"  ----strip----  " << strip_high <<std::endl; 
	//collect points with strip in order (-1 => not set yet)
	int first_pt_index_in_strip = -1;
	int last_pt_index_in_strip = -1;
	for(int i=low; i<= high; i++){
		if(first_pt_index_in_strip == -1){
			if(x[i] >= strip_low) first_pt_index_in_strip = i;
		}
		else {
			if(x[i] <= strip_high) last_pt_index_in_strip = i;
			// break;
		}
	}

	//if no point or just one point in strip
	if(last_pt_index_in_strip == -1) return d;


	// create a new vector for strip points and sort them by yy-coordinate
	vector<int> newx(last_pt_index_in_strip - first_pt_index_in_strip + 1);
	vector<int> newy(last_pt_index_in_strip - first_pt_index_in_strip + 1);

	for(int i=first_pt_index_in_strip; i<=last_pt_index_in_strip; i++){
		int index = i - first_pt_index_in_strip;
		newx[index] = x[i];
		newy[index] = y[i];
	}


	vector<vector<int> > z(newy.size() , vector<int> (2, 0));
	for(int i=0; i<newy.size(); i++){
		z[i][0] = newy[i];
		z[i][1] = i;
	}

	std::sort(z.begin(), z.end(), sortrow);
	vector<int> zx(x.size());
	vector<int> zy(x.size());

	for(int i=0; i<newy.size(); i++){
		int index = z[i][1];
		zx[i] = newx[index];
		zy[i] = newy[index];
	}


	//zx, zy sorted vector of points inside strip
	// find min dist inside strip
	double min_inside_strip = d;
	// std::cout<<"low = " <<low<<" high = "<<high <<std::endl;
	// std::cout<<"first = "<<first_pt_index_in_strip<<" second = "<<last_pt_index_in_strip<<"\n";
	for(int i=first_pt_index_in_strip; i< last_pt_index_in_strip; i++){
		// check upto 6 adjacent pts
		for(int k=1; k<=6; k++){
			// ignore if point is outside strip
			if(i+k > last_pt_index_in_strip) break;
			int index1 = i- first_pt_index_in_strip;
			int index2 = i- first_pt_index_in_strip + k;
			// std::cout<< "(" << zx[index1] << ","<< zy[index1]<<") , (" << zx[index2] << " ," <<zy[index2]<< ")\n";
			double dd = euclidean_distance(zx[index1], zy[index1], zx[index2], zy[index2]);
			min_inside_strip = min(min_inside_strip, dd);
		}
	}

	// since min_inside_strip <= d
	// std::cout<<"low = " <<low<<" high = "<<high <<std::endl;
	// std::cout<<min_inside_strip<< " " << d<< "\n";
	return min_inside_strip;
}





double minimal_distance(vector<int> x, vector<int> y) {
  //write your code here
	//sort points by x-coordinate( = O(nlogn) )
	vector<vector<int> > z( x.size() , vector<int> (2, 0));
	for(int i=0; i<x.size(); i++){
		z[i][0] = x[i];
		z[i][1] = i;
	}

	std::sort(z.begin(), z.end(), sortcol);

	vector<int> zx(x.size());
	vector<int> zy(x.size());

	for(int i=0; i<x.size(); i++){
		int index = z[i][1];
		zx[i] = x[index];
		zy[i] = y[index];
	}
	// sorted zx, zy
	//----------------------------------------

	//call helper function
	return helper(zx, zy, 0, x.size()-1);
}

double naive_algo(vector<int> x, vector<int> y){
	double min_dist = INF;
	for(int i=0; i<x.size(); i++){
		// std::cout<<min_dist<<std::endl;
		for(int j=i+1; j<x.size(); j++){
			// if(euclidean_distance(x[i],y[i],x[j],y[j]) < 10)std::cout<<x[i] <<" "<< y[i] <<" "<< x[j] <<" "<< y[j] <<" "<< euclidean_distance(x[i],y[i],x[j],y[j])<<"\n";
			min_dist = min(min_dist, euclidean_distance(x[i],y[i],x[j],y[j])); }
	}

	return min_dist;
}

void test_solution(){
	for(int j=0; j<2000; j++){
		int n = rand();
		n = n % 10000 + 7;
		std::cout<<n<<"-------------\n";

		vector<int>x(n); 
		vector<int>y(n);
		for(int i=0; i<n; i++){
			x[i] = rand() % 1000 - 283;
			y[i] = rand() % 1000 - 513;
		}

		//----------
		vector<vector<int> > z( x.size() , vector<int> (2, 0));
		for(int i=0; i<x.size(); i++){
			z[i][0] = x[i];
			z[i][1] = i;
		}

		std::sort(z.begin(), z.end(), sortcol);

		vector<int> zx(x.size());
		vector<int> zy(x.size());

		for(int i=0; i<x.size(); i++){
			int index = z[i][1];
			zx[i] = x[index];
			zy[i] = y[index];
		}
		//------------

		double r1 = minimal_distance(x,y);
		// std::cout<<"test_solution1\n";
		double r2 = naive_algo(x,y);
		// std::cout<<"test_solution2\n";
		double diff = abs(r1 - r2);
		// if(diff > .001){
		// 	std::cout<<n<<std::endl;
		// 	for(int i=0; i<n; i++){
		// 		std::cout << zx[i]<<" "<< zy[i] << std::endl;
		// 	}
		// 	std::cout << std::endl;
		// 	std::cout << r1 << "  "<<r2;
			// std::cout<<"\n-----------------------------------\n";
		// }
		assert(0.001 > diff);
	}
	return;
}


int main() {
  size_t n;
  std::cin >> n;
  vector<int> x(n);
  vector<int> y(n);
  for (size_t i = 0; i < n; i++) {
    std::cin >> x[i] >> y[i];
  }
  // test_solution();
  std::cout << std::fixed;
  std::cout << std::setprecision(9) << minimal_distance(x, y) << "\n";
}
