#include <iostream>
#include <vector>
#include <string>
#include <list>

using std::string;
using std::vector;
using std::list;
using std::cin;

static int it = 0;

struct person {
    string name;
    int number;

    person(string a, int b){
        name = a;
        number = b;
    }
};


void current_data_state(vector<vector<person>> &data){
    std::cout << "iteration = " << it << "\n";
    it++;
    for(int i=0; i<data.size(); i++){
        if(data[i].size()) std::cout << i << " = ";
        for(int j=0; j<data[i].size(); j++){
            std::cout << data[i][j].name << " ";
        }
        if(data[i].size())std::cout << "\n";
    }
    std::cout << "\n-------------------------------\n";
}


struct Query {
    string type, name;
    int number;
};

vector<Query> read_queries() {
    int n;
    cin >> n;
    vector<Query> queries(n);
    for (int i = 0; i < n; ++i) {
        cin >> queries[i].type;
        if (queries[i].type == "add")
            cin >> queries[i].number >> queries[i].name;
        else
            cin >> queries[i].number;
    }
    return queries;
}

void write_responses(const vector<string>& result) {
    for (size_t i = 0; i < result.size(); ++i)
        std::cout << result[i] << "\n";
}

int hash(int number){
    int a = 3;
    int b = 5634;
    int p = 10000019; //  next prime = 10000079
    int m = 1000;

    return ((a*number+b)%p)%m;
}

bool update_or_add_person(vector<person> &l, int number, string new_name){
    // std::cout << "adding:   "  <<number << " "<< new_name<<"\n";
    for(int i=0; i<l.size(); i++){
        if(l[i].number == number){
            l[i].name = new_name;
            return true;
        }
    }
    
    person new_person(new_name, number);
    l.push_back(new_person);
    return true;
}


bool delete_person(vector<person> &l, int number){
    // std::cout << "deleting: " << number << "\n";
    int p_index = -1;
    for(int i=0; i<l.size(); i++){
        if(l[i].number == number){
            p_index = i;
            break;
        }
    }
    
    if(p_index != -1){
        for(int i=p_index; i < l.size()-1; i++){
            l[i].name = l[i+1].name;
            l[i].number = l[i+1].number;
        }
        l.pop_back();
        return true;
    }
    return false; // contact not found for deletion
}

string find_person(vector<person> &l, int number){
    // std::cout << "finding:  " << number << "\n"; 
    bool found = false;
    // std::cout << "index = " << hash(number) << "\n";
    // if(hash(number) == 7) std::cout<<"size=" << l.size() << "\n";
    string result = "not found";
    for(int i=0; i<l.size(); i++){
        // std::cout<<"t=" <<l[i].number<<"\n";
        if(l[i].number == number){
            // std::cout <<"FOUND\n";
            result = l[i].name;
            found = true;
            break;
        }
    }
    // if(found) std::cout << "number found\n";
    // else std::cout << "not found\n";
    // std::cout << "\n-------------------------------\n";
    return result;
}

vector<string> process_queries(const vector<Query>& queries) {
    // std::cout << "ENTER PROCESS QUERIES...\n";
    // store result
    vector<string> result;
    // store data in vector of linklists
    vector<vector<person> > data(1000, vector<person>());

    for (size_t i = 0; i < queries.size(); ++i){
        // current_data_state(data);
        if(queries[i].type == "add"){
            int index = hash(queries[i].number);
            update_or_add_person(data[index], queries[i].number, queries[i].name);
        }
        else if(queries[i].type == "del"){
            int index = hash(queries[i].number);
            delete_person(data[index], queries[i].number);
        }
        else if(queries[i].type == "find"){
            int index = hash(queries[i].number);
            // std::cout<<"index = " << index << "  number = " << queries[i].number << "  size = " <<data[index].size() <<"\n";
            result.push_back(find_person(data[index], queries[i].number));
        }
        else{
            std::cout << "SOMETHING WRONG\n";
            std::cout << queries[i].type << "\n";
            break;
        }
    } 
    return result;
}


int main() {
    write_responses(process_queries(read_queries()));
    return 0;
}