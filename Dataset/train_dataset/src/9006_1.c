#include <bits/stdc++.h>
using LL = long long;
using namespace std;
class UnionFind{
private:
    vector<int> vec;
public:
    void init(int N){
        vec.resize(N,-1);
    }
    int root(int a){
        if(vec[a] < 0)return a;
        else return vec[a] = root(vec[a]);
    }
    bool connect(int a,int b){
        a = root(a);
        b = root(b);
        if(a == b)return false;
        if(vec[a] > vec[b])swap(a,b);
        vec[a] += vec[b];
        vec[b] = a;
        return true;
    }
    bool check(int a ,int b){
       return root(a) == root(b);
    }
};
vector<bool> sieve(int s){
    vector<bool> IsPrime;
    IsPrime.resize(s,true);

    IsPrime[0]=false;
    IsPrime[1]=false;
    for(int i = 0;i <=s;i++)
        if(IsPrime[i])
            for(int j =i+1;j <= s;j++)
                if(j%i==0)
                    IsPrime[j]=false;

    return IsPrime;
}
int main(){
    int N;cin >> N;
    vector<pair<int,int>> vec;
    UnionFind Uni;
    Uni.init(N);
    for(int a = 0;a < N;a++){
        int b;cin >> b;
        vec.push_back(make_pair(b,a));
    }
    vector<bool> pR = sieve(10010);
    vector<int> prime;
    for(int a = 0;a < pR.size();a++){
        if(pR[a])prime.push_back(a);
    }

    for(int a = 0;a < prime.size();a++){
        //cout<<prime.at(a)<<endl;
        int s = -1;
        for(int b = 0;b < N;b++){
            if(!(vec.at(b).first%prime.at(a))){
                if(s != -1){
                   // cout<<s<<" "<<b<<" "<<vec.at(b).first<<" "<<prime.at(a)<<endl;
                    Uni.connect(s,b);
                }else{
                    s = b;
                }
            }
        }
    }
    vector<pair<int,int>> ins = vec;
    sort(ins.begin(),ins.end());
    for(int a = 0;a < N;a++){
        if(!Uni.check(ins.at(a).second,a)){
            cout<<0<<endl;
            return 0;
        }
    }
    cout<<1<<endl;
}
//2t+2
