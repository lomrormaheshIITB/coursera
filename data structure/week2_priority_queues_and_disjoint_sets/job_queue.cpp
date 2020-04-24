#include <iostream>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <time.h>

using std::vector;
using std::cin;
using std::cout;
// using std::clock();
// using std::clock_t;

// void print_vector(vector<int> &v){
//   for(auto it=v.begin(); it != v.end(); it++)
//     std::cout<<*it << " ";
//   std::cout << "\n";
//   return;
// }

class JobQueue {
 private:
  int num_workers_;
  vector<int> jobs_;

  // vector<int> assigned_workers_;
  vector<int> my_assigned_workers_;
  // vector<long long> start_times_;
  vector<long long> my_start_times_;

  void WriteResponse() const {
    // int diff = 0;
    for (int i = 0; i < jobs_.size(); ++i) {
      // cout << assigned_workers_[i] << " " << start_times_[i] << "\n";
      cout << my_assigned_workers_[i] << " " << my_start_times_[i] << "\n";
      // cout << "-----------------------------------\n";
      // if(assigned_workers_[i] != my_assigned_workers_[i] or start_times_[i] != my_start_times_[i]){
        // diff++;
        // cout << assigned_workers_[i] << " " << start_times_[i] << "\n";
        // cout << my_assigned_workers_[i] << " " << my_start_times_[i] << "\n";
        // cout << "-----------------------------------\n";
      // }
    }

    // cout<<"diff = " << diff << "\n";
  }

  // void my_WriteResponse() const {
  //   for (int i = 0; i < jobs_.size(); ++i) {
  //     cout << my_assigned_workers_[i] << " " << my_start_times_[i] << "\n";
  //   }
  // }

  void ReadData() {
    int m;
    cin >> num_workers_ >> m;
    jobs_.resize(m);
    for(int i = 0; i < m; ++i)
      cin >> jobs_[i];

    // int m;
    // m = 99999; // < 10^5
    // num_workers_ = 1112; // < 10^5
    // jobs_.resize(m);
    // for(int i = 0; i < m; ++i)
    //   jobs_[i] = rand() % 999999999 + 23; // < 10^9

  }

  // void AssignJobs() {
  //   // TODO: replace this code with a faster algorithm.
  //   assigned_workers_.resize(jobs_.size());
  //   start_times_.resize(jobs_.size());
  //   vector<long long> next_free_time(num_workers_, 0);

  //   for (int i = 0; i < jobs_.size(); ++i) {
  //     int duration = jobs_[i];
  //     int next_worker = 0;
  //     for (int j = 0; j < num_workers_; ++j) {
  //       if (next_free_time[j] < next_free_time[next_worker])
  //         next_worker = j;
  //     }
  //     assigned_workers_[i] = next_worker;
  //     start_times_[i] = next_free_time[next_worker];
  //     next_free_time[next_worker] += duration;
  //   }

  //   // int job_left = jobs_.size();
  //   // int next_frame = 0;
  //   // int next_free = 0;
  //   // int current_time = 0;
  //   // int index = 0;

  //   // while(index < jobs_.size()){
  //   //   // int index = jobs_.size()-job_left;
  //   //   current_time += next_frame;
  //   //   assigned_workers_[index]=next_free;
  //   //   start_times_[index]=current_time;
  //   //   next_free_time[next_free]=jobs_[index];
  //   //   // job_left--;
  //   //   index++;

  //   //   // CALCULATE NEXT_FRAME AND next_free AND REST LEFT_TIME OF EACH THREAD(WORKER)
  //   //   next_frame = next_free_time[0];
  //   //   next_free = 0;
  //   //   for(int i=0; i<num_workers_; i++)
  //   //     if(next_frame > next_free_time[i]){
  //   //       next_frame = next_free_time[i];
  //   //       next_free=i;
  //   //     }

  //   //   for(int i=0; i<num_workers_; i++)
  //   //     next_free_time[i] -= next_frame;

  //   // }
  // }

  void my_AssignJobs() {
    my_assigned_workers_.resize(jobs_.size());
    my_start_times_.resize(jobs_.size());
    vector<long long> next_free_time(num_workers_, 0);

    long long next_frame = 0;
    int next_free = 0;
    long long current_time = 0;
    int index = 0;

    while(index < jobs_.size()){
      current_time += next_frame;
      my_assigned_workers_[index]=next_free;
      my_start_times_[index]=current_time;
      next_free_time[next_free]=jobs_[index];
      index++;

      // CALCULATE NEXT_FRAME AND next_free AND REST LEFT_TIME OF EACH THREAD(WORKER)
      next_frame = next_free_time[0];
      next_free = 0;
      for(int i=0; i<num_workers_; i++)
        if(next_frame > next_free_time[i]){
          next_frame = next_free_time[i];
          next_free=i;
        }

      for(int i=0; i<num_workers_; i++)
        next_free_time[i] -= next_frame;

    }
  }

 public:
  void Solve() {
    ReadData();
    // AssignJobs();
    my_AssignJobs();
    WriteResponse();
    // std::cout<<"My answer:\n";
    // my_WriteResponse();
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
