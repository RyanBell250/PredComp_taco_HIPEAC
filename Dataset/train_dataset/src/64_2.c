#include<bits/stdc++.h>
using namespace std;

#define int long long

#define rep(i,n) for(int i=0;i<(n);i++)
#define all(v) (v).begin(),(v).end()
#define pb push_back
#define fi first
#define se second

typedef vector<int>vint;
typedef pair<int,int>pint;
typedef vector<pint>vpint;

template<typename A,typename B>inline void chmin(A &a,B b){if(a>b)a=b;}
template<typename A,typename B>inline void chmax(A &a,B b){if(a<b)a=b;}

int N,M;
int C[111111];
int A[111111],B[111111];

vint G[111111];
vint rG[111111];
bool used[111111];
int cmp[111111];
vint vs;

void dfs(int v){
    used[v]=1;
    for(int i=0;i<G[v].size();i++){
        if(!used[G[v][i]])dfs(G[v][i]);
    }
    vs.pb(v);
}

void rdfs(int v,int k){
    used[v]=true;
    cmp[v]=k;
    for(int i=0;i<rG[v].size();i++){
        if(!used[rG[v][i]])rdfs(rG[v][i],k);
    }
}


vector<vint>lis;
vector<vint>H;
bool isbi[111111];
int col[111111];

bool paint(int v,int c){
    used[v]=1;
    col[v]=c;
    for(auto u:H[v]){
        if(used[u]){
            if(col[u]==c)return false;
            continue;
        }
        if(!paint(u,c^1))return false;
    }
    return true;
}

int dp[111111][2];

signed main(){
    scanf("%lld%lld",&N,&M);
    rep(i,N)scanf("%lld",&C[i]);
    rep(i,M){
        scanf("%lld%lld",&A[i],&B[i]);
        G[A[i]].pb(B[i]);
        rG[B[i]].pb(A[i]);
    }

    rep(i,N)if(!used[i])dfs(i);
    memset(used,0,sizeof(used));
    int K=0;
    for(int i=vs.size()-1;i>=0;i--){
        if(!used[vs[i]])rdfs(vs[i],K++);
    }
    lis.resize(K);
    rep(i,N)lis[cmp[i]].pb(i);

    H.resize(N);
    rep(i,M)if(cmp[A[i]]==cmp[B[i]])H[A[i]].pb(B[i]);
    memset(used,0,sizeof(used));
    rep(i,K){
        int v=lis[i][0];
        isbi[i]=paint(v,0);
    }

    rep(i,N)G[i].clear();
    rep(i,M){
        int x=cmp[A[i]];
        int y=cmp[B[i]];
        if(x!=y)G[x].pb(y);
    }
    vs.clear();
    memset(used,0,sizeof(used));
    dfs(cmp[0]);
    reverse(all(vs));

    vector<vint>GG(N);
    rep(i,M)GG[A[i]].pb(B[i]);

    fill_n(*dp,111111*2,INT_MIN);
    dp[vs[0]][0]=0;
    for(auto v:vs){
        int sum[2]={};
        for(auto u:lis[v])sum[col[u]]+=C[u];

        if(!isbi[v]){
            dp[v][0]=max(dp[v][0],dp[v][1]);
            dp[v][1]=dp[v][0];
            dp[v][0]+=sum[0]+sum[1];
            dp[v][1]+=sum[0]+sum[1];
        }
        else{
            dp[v][0]+=sum[col[lis[v][0]]];
            dp[v][1]+=sum[col[lis[v][0]]^1];
        }

        rep(i,2){
            for(auto w:lis[v]){
                for(auto u:GG[w]){
                    if(cmp[u]==v)continue;
                    int p=i^(col[lis[v][0]]!=col[w])^1;
                    p^=col[lis[cmp[u]][0]]!=col[u];
                    chmax(dp[cmp[u]][p],dp[v][i]);
                }
            }
        }

    }

    int ans=0;
    rep(i,K)rep(j,2)chmax(ans,dp[i][j]);
    cout<<ans<<endl;
    return 0;
}