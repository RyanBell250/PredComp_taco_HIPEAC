
#include<iostream>
#include<vector>
#include<tuple>
#include<algorithm>
using namespace std;
const int MOD = 12345678;
const int NIL = -1;
class Numoeba {
public:
    Numoeba(const int n) :max_cell_(1), root_(0) {create_cell(n);}
    tuple<int, int> die() {
        for(int step = 1; step <= 500; ++step) {
            int t = dead_.size() - count(dead_.begin(), dead_.end(), true);
            max_cell_ = max(max_cell_, t);
            vector<int> candidate;
            int new_leader_id, new_leader_n = NIL;
            if(traverse(root_, NIL, candidate, new_leader_id, new_leader_n)) return tuple<int, int>(step, max_cell_);
            for(auto& e: edge_) for(int i = 0; i < e.size(); ++i) if(dead_[e[i]]) e.erase(e.begin() + i--);
            for(const auto& c: candidate) {
                int n = (numbosome_[c] + 1) / 2;
                if(!(n & 1)) ++n;
                add_child(c, create_cell(n));
            }
            if(new_leader_id == NIL) continue;
            root_ = new_leader_id;
            int n = (numbosome_[root_] + 1) / 2;
            if(!(n & 1)) --n;
            add_child(root_, create_cell(n));
        }
        return tuple<int, int>(NIL, max_cell_);
    }
private:
    bool traverse(const int current, const int previous, vector<int>& candidate, int& new_leader_id, int& new_leader_n) {
        int pn = numbosome_[current];
        if(update(current) == 1) {
            dead_[current] = true;
            if(current == root_) return true;
            if(edge_[current].size() == 2) {
                int next = edge_[current][0];
                if(next == previous) next = edge_[current][1];
                for(auto& id: edge_[previous]) if(id == current) id = next;
                for(auto& id: edge_[next]) if(id == current) id = previous;
                return traverse(next, previous, candidate, new_leader_id, new_leader_n);
            }
            for(const auto& next: edge_[current]) if(next != previous) erase(next, current);
            return false;
        }
        if(numbosome_[current] > pn && edge_[current].size() <= 1) candidate.push_back(current);
        if(numbosome_[current] == new_leader_n) new_leader_id = NIL;
        if(numbosome_[current] > new_leader_n) {
            new_leader_n = numbosome_[current];
            new_leader_id = current;
        }
        for(const auto& next: edge_[current]) {
            if(next == previous) continue;
            if(traverse(next, current, candidate, new_leader_id, new_leader_n)) return true;
        }
        return false;
    }
    void erase(const int current, const int previous) {
        dead_[current] = true;
        for(const auto& next: edge_[current]) if(next != previous) erase(next, current);
    }
    int create_cell(const int n) {
        numbosome_.push_back(n);
        dead_.push_back(false);
        edge_.push_back(vector<int>());
        return (dead_.size() - 1);
    }
    void add_child(const int pid, const int cid) {
        edge_[pid].push_back(cid);
        edge_[cid].push_back(pid);
    }
    int update(const int id) {
        numbosome_[id] = numbosome_[id] * 3 + 1;
        while(!(numbosome_[id] & 1)) numbosome_[id] >>= 1;
        if(numbosome_[id] > MOD) numbosome_[id] -= MOD;
        return numbosome_[id];
    }
    int root_;
    int max_cell_;
    vector<int> numbosome_;
    vector<bool> dead_;
    vector<vector<int>> edge_;
public:
void print(){
cout<<"root: "<<root_<<endl;
cout<<"dead: ";for(const auto&d:dead_)cout<<" "<<d;cout<<endl;
cout<<"numb: ";for(const auto&d:numbosome_)cout<<" "<<d;cout<<endl;
cout<<dead_.size()<<endl;
}
};
int main() {
    int k;
    while(cin >> k, k) {
        Numoeba n(k);
        int step, numbosome;
        tie(step, numbosome) = n.die();
        cout << step << " " << numbosome << endl;
    }
}