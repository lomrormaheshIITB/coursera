#include <iostream>
#include <queue>
#include <vector>
#include <queue>

struct Request {
    Request(int arrival_time, int process_time):
        arrival_time(arrival_time),
        process_time(process_time)
    {}

    int arrival_time;
    int process_time;
};

struct Response {
    Response(bool dropped, int start_time):
        dropped(dropped),
        start_time(start_time)
    {}

    bool dropped;
    int start_time;
};

class Buffer {
public:
    Buffer(int size):
        size_(size),
        finish_time_()
    {}

    Response Process(const Request &request) {
        // write your code here
    }
private:
    int size_;
    std::queue <int> finish_time_;
};

std::vector <Request> ReadRequests() {
    std::vector <Request> requests;
    int count;
    std::cin >> count;
    for (int i = 0; i < count; ++i) {
        int arrival_time, process_time;
        std::cin >> arrival_time >> process_time;
        requests.push_back(Request(arrival_time, process_time));
    }
    return requests;
}

std::vector <Response> ProcessRequests(const std::vector <Request> &requests, Buffer *buffer) {
    std::vector <Response> responses;
    for (int i = 0; i < requests.size(); ++i)
        responses.push_back(buffer->Process(requests[i]));
    return responses;
}

void PrintResponses(const std::vector <Response> &responses) {
    for (int i = 0; i < responses.size(); ++i)
        std::cout << (responses[i].dropped ? -1 : responses[i].start_time) << std::endl;
}


std::vector<int> Simulation(int buf_size, int num_packets, std::vector<int> &arrival, std::vector<int> &processing){
    std::vector<int> output(num_packets);
    if(buf_size == 0){
        for(int i=0; i<num_packets; i++){
            output[i] = -1;
        }
        return output;
    }

    std::queue<int> buffer;
    std::vector<int> start_time(num_packets);
    std::vector<int> end_time(num_packets);
    std::vector<int> drop(num_packets);

    int current_packet = 0;
    int current_time = 0;
    while(current_packet < num_packets){
        // packets whose end_time is before current_time should be removed from buffer
        current_time = arrival[current_packet];
        while(end_time[buffer.front()] <= current_time and !buffer.empty()){
            if(buffer.empty()) break;
            else buffer.pop();
        }

        if(current_packet == 0){
            buffer.push(current_packet);  // push current_packet into buffer
            drop[current_packet] = 0;  // not dropped
            start_time[current_packet] = arrival[current_packet];
            end_time[current_packet] = start_time[current_packet] + processing[current_packet]; 
            // current_time = arrival[current_packet];
            current_packet++;
            // while(end_time[buffer.front()] <= current_time){   // packets 
            //     if(buffer.empty()) break;
            //     buffer.pop();
            // }
        }
        else if(buffer.size() < buf_size){
            buffer.push(current_packet);  // push current_packet into buffer
            drop[current_packet] = 0;  // not dropped
            start_time[current_packet] = std::max(end_time[current_packet-1], arrival[current_packet]);
            end_time[current_packet] = start_time[current_packet] + processing[current_packet];
            current_packet++;
        }
        else{
            drop[current_packet] = 1;  // dropped
            // see dropped packet as 0 time processing packet as it didn't get processed
            start_time[current_packet] = end_time[current_packet-1];  
            end_time[current_packet] = end_time[current_packet-1];
            // current_time = arrival[current_packet];
            current_packet++;
            // while(end_time[buffer.front()] <= current_time){
                // if(buffer.empty()) break;
                // buffer.pop();
            // }

        }


    }

    for(int i=0; i<num_packets; i++){
        if(drop[i]) output[i] = -1;
        else output[i] = start_time[i];
    }

    return output;
}


int main() {
    // int size;
    // std::cin >> size;
    // std::vector <Request> requests = ReadRequests();

    // Buffer buffer(size);
    // std::vector <Response> responses = ProcessRequests(requests, &buffer);

    // PrintResponses(responses);
    // return 0;

    int buf_size;
    int num_packets;
    std::cin >> buf_size >> num_packets;

    std::vector <int> arrival(num_packets);
    std::vector <int> processing(num_packets);

    for(int i=0; i<num_packets; i++)
        std::cin >> arrival[i] >> processing[i];

    std::vector <int> output = Simulation(buf_size, num_packets, arrival, processing);
    for(int i=0; i<num_packets; i++)
        std::cout << output[i] << "\n";
}
