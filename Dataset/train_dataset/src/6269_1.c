#include<bits/stdc++.h>
using namespace std;
#define ALL(x) x.begin(),x.end()
#define rep(i,n) for(int i=0;i<n;i++)
#define debug(v) cout<<#v<<":";for(auto x:v){cout<<x<<' ';}cout<<endl; 
#define INF 1000000000
#define mod 1000000007
using ll=long long;
const ll LINF = 1001002003004005006ll;
int dx[]={1,0,-1,0};
int dy[]={0,1,0,-1};
ll gcd(ll a,ll b){return b?gcd(b,a%b):a;}
template<class T>bool chmax(T &a, const T &b) { if (a<b) { a=b; return 1; } return 0; }
template<class T>bool chmin(T &a, const T &b) { if (b<a) { a=b; return 1; } return 0; }
template<typename T>
struct edge{
    int src,to;
    T cost;
    edge(int to,T cost):src(-1),to(to),cost(cost){}
    edge(int src,int to,T cost):src(src),to(to),cost(cost){}
};
template<typename T>
vector<T> BellmanFord(vector<edge<T>> &edges,int V,int s){
    const auto TINF=numeric_limits<T>::max();
    vector<T> dist(V,TINF);
    dist[s]=0;
    for(int i=0;i<V-1;i++){
        for(auto &e:edges){
            if(dist[e.src]==TINF) continue;
            dist[e.to]=min(dist[e.to],dist[e.src]+e.cost);
        }
    }
    for(auto &e:edges){
        if(dist[e.src]==TINF) continue;
        if(dist[e.src]+e.cost<dist[e.to]) return vector<T>();
    }
    return dist;
}
signed main(){
    cin.tie(0);
    ios::sync_with_stdio(0);
    int N,C;cin>>N>>C;
    vector<edge<int>> es;
    vector<tuple<int,int,int,int>> undif;
    rep(i,C){
        string s;cin>>s;
        int u=0,v=0,o,w=0,pl=0;
        int idx=0;
        for(;;){
            if(0<=(s[idx]-'0') and (s[idx]-'0')<=9){
                u=10*u+(s[idx]-'0');
            }else{
                break;
            }
            idx++;
        }
        if(s[idx]=='<')o=-1,idx+=2;
        else if(s[idx]=='*') o=0,idx++;
        else if(s[idx]=='>')o=1,idx+=2;
        for(;;){
            if(0<=(s[idx]-'0') and (s[idx]-'0')<=9){
                v=10*v+(s[idx]-'0');
            }else{
                break;
            }
            idx++;
        }
        if(s[idx]=='+') pl=1;
        idx++;
        for(;idx<s.size();){
            w=w*10+(s[idx]-'0');
            idx++;
        }
        u--,v--;
        if(o==1) swap(u,v);
        if(o!=0 and pl==0){
            es.push_back(edge<int>(v,u,0));
            es.push_back(edge<int>(u,v,w));
        }
        if(o!=0 and pl==1){
            es.push_back(edge<int>(v,u,0));
            es.push_back(edge<int>(v,u,-w));
        }
        if(o==0){
            undif.push_back(make_tuple(u,v,w,pl));
        }
    }
    int M=undif.size(),ans=-1;
    for(int bit=0;bit<(1<<M);bit++){
        rep(i,M){
            int u=get<0>(undif[i]),v=get<1>(undif[i]),w=get<2>(undif[i]),pl=get<3>(undif[i]);
            if((bit>>i)&1) swap(u,v);
            es.push_back(edge<int>(v,u,0));
            if(pl==0){
                es.push_back(edge<int>(u,v,w));
            }else{
                es.push_back(edge<int>(v,u,-w));
            }
        }
        auto dis=BellmanFord(es,N,0);
        rep(i,2*M) es.pop_back();
        if(dis.empty() or *min_element(ALL(dis))<0) continue;
        chmax(ans,*max_element(ALL(dis)));
    }
    if(ans>INF) cout<<"inf"<<endl;
    else cout<<ans<<endl;
    return 0;
}
