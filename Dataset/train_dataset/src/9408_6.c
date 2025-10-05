#include<iomanip>
#include<limits>
#include<thread>
#include<utility>
#include<iostream>
#include<string>
#include<algorithm>
#include<set>
#include<map>
#include<vector>
#include<stack>
#include<queue>
#include<cmath>
#include<numeric>
#include<cassert>
#include<random>
#include<chrono>
#include<unordered_set>
#include<unordered_map>
#include<fstream>
#include<list>
#include<functional>
#include<bitset>
#include<complex>
#include<tuple>
using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
typedef pair<ll,ll> pll;
typedef long double D;
#define F first
#define S second
const ll E=1e18+7;
const ll MOD=1000000007;
class LCA{
private:
    typedef pair<ll,vector<ll>> node; 
    ll root;
    ll v;
    vector<node> tree;
    vector<vector<ll>> E;
    ll High; 
    void bfs(){
        tree[root]={0,{root}};
        queue<ll> q;
        q.push(root);
        vector<bool> done(v,false);
        while(!q.empty()){
            ll where=q.front();
            q.pop();
            if(done[where]){continue;}
            done[where]=true;
            for(int i=0;i<E[where].size();i++){
                if(!done[E[where][i]]){
                    tree[E[where][i]].F=tree[where].F+1;
                    tree[E[where][i]].S={where};
                    q.push(E[where][i]);
                }
            }
        }
    }
public:
    LCA(ll v,ll root):v(v),root(root){
        tree.resize(v);
        E.resize(v);
    }
    void add_edge(ll from,ll to){
        E[from].push_back(to);
    }
    void mk_tree(){
        bfs();
        bool j=true;
        for(int i=0;j;i++){
            j=false;
            for(int t=0;t<v;t++){
                ll P=tree[t].S[i];
                P=tree[P].S[i];
                tree[t].S.push_back(P);
                if(P!=root){j=true;}
            }
        }
        High=tree[root].S.size();
    }
    ll search_parent(ll a,ll h){
        if(tree[a].F<=h){return root;}
        for(ll i=High-1;i>=0;i--){
            if((1<<i)&h){a=tree[a].S[i];}
        }
        return a;
    }
    ll search_lca(ll a,ll b){
        ll dif=tree[a].F-tree[b].F;
        if(0>dif){swap(a,b); dif=abs(dif);}
        a=search_parent(a,dif);
        for(ll i=High-1;i>=0;i--){
            if(tree[a].S[i]!=tree[b].S[i]){
                a=tree[a].S[i];
                b=tree[b].S[i];
            }
        }
        while(a!=b){
            a=tree[a].S[0];
            b=tree[b].S[0];
        }
        return a;
    }
    ll high(ll a){
        return tree[a].F;
    }
};
const ll mod=MOD;
ll mod_pow(ll a,ll x){
    a%=mod;
    ll ans=1;
    while(x>0){
        if(x&1){ans*=a; ans%=mod;}
        a*=a;
        a%=mod;
        x>>=1;
    }
    return ans;
}
pll Ex_gcd(ll a,ll b){
    if(b==0){return {1,0};}
    pll ret=Ex_gcd(b,a%b);
    ret.F-=a/b*ret.S;
    return {ret.S,ret.F};
}
ll prime_R(ll a){
    return mod_pow(a,mod-2);
}
ll R(ll a){
    ll ret=Ex_gcd(a,mod).F;
    ret%=mod;
    if(ret<0){ret+=mod;}
    return ret;
}
int main(){
    ll n,m;
    cin>>n>>m;
    LCA lca(n,n-1);
    vector<ll> Fat(m-n+1,0);
    for(int i=1;i<n;i++){
        ll u,v;
        cin>>u>>v;
        u--; v--;
        lca.add_edge(u,v);
        lca.add_edge(v,u);
    }
    lca.mk_tree();
    for(ll i=n;i<=m;i++){
        ll u,v;
        cin>>u>>v;
        u--; v--;
        ll m=lca.search_lca(u,v);
        while(u!=m){Fat[i-n]|=1LL<<u; u=lca.search_parent(u,1);}
        while(v!=m){Fat[i-n]|=1LL<<v; v=lca.search_parent(v,1);}
    }
    vector<ll> cnt(1LL<<(n-1),0);
    vector<ll> bitcnt(1LL<<(n-1),0);
    for(ll i=0;i<(1LL<<(n-1));i++){
        for(int j=0;j<n-1;j++){
            if(i>>j&1){bitcnt[i]++;}
        }
        for(auto &I:Fat){
            if((I&i)==I){cnt[i]++;}
        }
    }
    vector<pll> dp(1LL<<(n-1),{0,0});
    vector<ll> F(m+11,1);
    for(ll i=1;i<=m+10;i++){F[i]=F[i-1]*i%MOD;}
    vector<ll> RF(m+11,1);
    for(ll i=1;i<=m+10;i++){RF[i]=RF[i-1]*R(i)%MOD;}
    dp.back()={1,0};
    for(ll i=(1LL<<(n-1))-1;i>=0;i--){
        for(int j=0;j<n-1;j++){
            if(i>>j&1){continue;}
            ll N=i|(1LL<<j);
            dp[i].F+=dp[N].F*F[m-bitcnt[N]-cnt[i]]%MOD*RF[m-bitcnt[N]-cnt[N]]%MOD;
            dp[i].F%=MOD;
            dp[i].S+=dp[N].S*F[m-bitcnt[i]-cnt[i]]%MOD*RF[m-bitcnt[i]-cnt[N]]%MOD;
            dp[i].S+=(n-bitcnt[N])*dp[N].F%MOD*F[m-bitcnt[N]-cnt[i]]%MOD*RF[m-bitcnt[N]-cnt[N]]%MOD;
            dp[i].S%=MOD;
        }
    }
    ll ans=dp[0].S;
    ans%=MOD;
    if(ans<0){ans+=MOD;}
    cout<<ans<<endl;
    return 0;
}
