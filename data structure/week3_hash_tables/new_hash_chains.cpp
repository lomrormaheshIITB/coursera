#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using std::string;
using std::vector;
using std::cin;

struct Query {
    string type, s;
    size_t ind;
};

class QueryProcessor {
    int bucket_count;
    // store all strings in one vector
    vector<vector<string> >data;
    // vector<string> elems;
    size_t hash_func(const string& s) const {
        static const size_t multiplier = 263;
        static const size_t prime = 1000000007;
        unsigned long long hash = 0;
        for (int i = static_cast<int> (s.size()) - 1; i >= 0; --i)
            hash = (hash * multiplier + s[i]) % prime;
        return hash % bucket_count;
    }

public:
    explicit QueryProcessor(int bucket_count): bucket_count(bucket_count) {}

    Query readQuery() const {
        Query query;
        cin >> query.type;
        if (query.type != "check")
            cin >> query.s;
        else
            cin >> query.ind;
        return query;
    }

    void writeSearchResult(bool was_found) const {
        std::cout << (was_found ? "yes\n" : "no\n");
    }

    void add_element(string s, int index){
        bool is_already_present = find_element(s, index);
        if(!is_already_present){
            data[index].push_back(s);
        }
    }

    void check_list(int index){
        for(int i=data[index].size()-1; i>=0; --i){
            std::cout<< data[index][i] << " ";
        }
        std::cout << "\n";
    }

    bool find_element(string s, int index){
        bool found = false;
        for(int i=0; i<data[index].size(); i++){
            if(data[index][i] == s){
                found = true;
                break;
            }
        }
        return found;
    }

    void del_element(string s, int index){
        int place = -1;
        for(int i=0; i<data[index].size(); i++){
            if(data[index][i] == s){
                place = i;
                break;
            }
        }
        if(place != -1){
            for(int i=place; i<data[index].size()-1; i++){
                data[index][i] = data[index][i+1];
            }
            data[index].pop_back();
        }
    }

    void processQuery(const Query& query) {
        if(query.type == "add"){
            int index = hash_func(query.s);
            add_element(query.s, index);
        }
        else if(query.type == "check"){
            check_list(query.ind);
        }
        else if(query.type == "find"){
            int index = hash_func(query.s);
            bool found = find_element(query.s, index);
            writeSearchResult(found);
        }
        else if(query.type == "del"){
            int index = hash_func(query.s);
            del_element(query.s, index);
        }
        else{
            std::cout << "SOME THING WORNG\n";
            return;
        }
    }

    void processQueries() {
        // resize data
        data.resize(bucket_count, vector<string>());
        int n;
        cin >> n;
        for (int i = 0; i < n; ++i)
            processQuery(readQuery());
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    int bucket_count;
    cin >> bucket_count;
    QueryProcessor proc(bucket_count);
    proc.processQueries();
    return 0;
}
