#include<bits/stdc++.h>
using namespace std;
#define int long long
#define rep(i,n) for(int i=0;i<(n);i++)
#define pb push_back
#define all(v) (v).begin(),(v).end()
#define fi first
#define se second
typedef vector<int>vint;
typedef pair<int,int>pint;
typedef vector<pint>vpint;
template<typename A,typename B>inline void chmin(A &a,B b){if(a>b)a=b;}
template<typename A,typename B>inline void chmax(A &a,B b){if(a<b)a=b;}
int N;
string S[222222];
int dp[222222];
signed main(){
    cin>>N;
    rep(i,N)cin>>S[i];
    int dp2[26];
    rep(i,26)dp2[i]=INT_MAX;
    dp2[S[0][0]-'a']=0;
    rep(i,N){
        dp[i]=dp2[S[i][0]-'a']+1;
        chmin(dp2[S[i].back()-'a'],dp[i]);
    }
    cout<<dp[N-1]<<endl;
    return 0;
}
