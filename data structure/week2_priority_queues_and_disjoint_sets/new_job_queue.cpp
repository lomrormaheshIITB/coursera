#include <iostream>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <time.h>

using std::vector;
using std::cin;
using std::cout;


// Class MinHeap
class MinHeap{
private:
	int num_workers_;

public:
  // (rank(index), next_free_time)
	vector<vector<long long> > data; 

	// Constructor
	MinHeap(int n){
		num_workers_ = n;
		data.resize(n, vector<long long>(2));
		for(int i=0; i<n; i++){
      data[i][0]=i;
      data[i][1]=0;
    } 
	}

  //PRINT HEAP
  void print_heap(){
    std::cout << "PRINTING HEAP....\n";
    for(int i=0; i<num_workers_; i++){
      std::cout<< data[i][0] << " " << data[i][1] << "\n";
    }
    std::cout << "PRINTED HEAP....\n";
  }

	int Parent(int i){
    return (i-1)/2;
	}

	int LeftChild(int i){
    return 2*i+1;
	}

	int RightChild(int i){
    return 2*i+2;
	}

	int CompareWorker(vector<long long>& w1, vector<long long> &w2){
    if(w1[1] != w2[1])
      return w1[1] < w2[1];
    else
      return w1[0] < w2[0];
	}

	void SiftUp(int i){
    if(i*CompareWorker(data[i], data[Parent(i)])){
      long long p0 = data[Parent(i)][0];
      long long p1 = data[Parent(i)][1];
      data[Parent(i)][0] = data[i][0];
      data[Parent(i)][1] = data[i][1];
      data[i][0] = p0;
      data[i][1] = p1;
      SiftUp(Parent(i));
    }
	}

	void SiftDown(int i){
    int min_index = i;
    int l = LeftChild(i);
    if(l < num_workers_ and  CompareWorker(data[l], data[min_index]))
      min_index = l;
    int r = RightChild(i);
    if(r < num_workers_ and CompareWorker(data[r], data[min_index]))
      min_index = r;

    if(min_index != i){
      long long m0 = data[min_index][0];
      long long m1 = data[min_index][1];
      data[min_index][0] = data[i][0];
      data[min_index][1] = data[i][1];
      data[i][0] = m0;
      data[i][1] = m1;
      SiftDown(min_index);
    }
	}

  void ChangePriority(int index, long long priority){
    // std::cout<<"NEW PRIORITY =  " << priority << "\n";
    long long old_p = data[index][1];
    data[index][1] = priority;
    if(priority < old_p)
      SiftUp(index);
    else
      SiftDown(index);
    SiftDown(index);
  }

  void RepairHeap(){
    for(int i=num_workers_/2; i>=0; i--)
      SiftDown(i);
  }


};


//Class Jobqueue
class JobQueue {
 private:
  int num_workers_;
  vector<int> jobs_;

  vector<int> assigned_workers_;
  vector<long long> start_times_;

   void WriteResponse() const {
    for (int i = 0; i < jobs_.size(); ++i) {
      cout << assigned_workers_[i] << " " << start_times_[i] << "\n";
    }
  }


  void ReadData() {
    int m;
    cin >> num_workers_ >> m;
    jobs_.resize(m);
    for(int i = 0; i < m; ++i)
      cin >> jobs_[i];
  }

void AssignJobs() {
    // TODO: replace this code with a faster algorithm.
    assigned_workers_.resize(jobs_.size());
    start_times_.resize(jobs_.size());
    vector<long long> next_free_time(num_workers_, 0);

    // Create instance of MinHeap
    MinHeap min_heap = MinHeap(num_workers_);

    // for(int i=0; i<num_workers_; i++){
    //   // min_heap.print_heap();
    //   assigned_workers_[i] = i;
    //   start_times_[i] = 0;
    //   min_heap.ChangePriority(0, min_heap.data[0][1] + jobs_[i]);
    // }

    for (int i = 0; i < jobs_.size(); ++i) {
      // min_heap.print_heap();
      assigned_workers_[i] = min_heap.data[0][0];
      start_times_[i] = min_heap.data[0][1];
      min_heap.ChangePriority(0, min_heap.data[0][1] + jobs_[i]);
    }
}

 public:
  void Solve() {
    ReadData();
    AssignJobs();
    WriteResponse();
  }
 };

int main() {
  srand(time(NULL));

  std::ios_base::sync_with_stdio(false);
  // clock_t begin = clock();
  JobQueue job_queue;
  job_queue.Solve();
  // clock_t end = clock();

  // std::cout << "TIME = " << (end - begin) / CLOCKS_PER_SEC << std::endl;
  // std::cout << (end - begin) << " " <<CLOCKS_PER_SEC << std::endl;
  return 0;
}