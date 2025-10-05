#include<bits/stdc++.h>
using namespace std;
using Int = long long;
using ll = long long;
template<typename T1,typename T2> inline void chmin(T1 &a,T2 b){if(a>b)a=b;};
template<typename T1,typename T2> inline void chmax(T1 &a,T2 b){if(a<b)a=b;};
const Int INF = 1e15;
Int a,e,s,r;
const Int MAX = 111;
Int dp[MAX][MAX];
Int calc(Int p,string x,string y){
  Int n=x.size(),m=y.size();
  x=x.substr(p)+x.substr(0,p);  
  x+='%';y+='^';
  for(Int i=0;i<MAX;i++)
    for(Int j=0;j<MAX;j++)         
      dp[i][j]=INF; 
  dp[0][0]=0; 
  for(Int i=0;i<=n;i++){
    for(Int j=0;j<=m;j++){
      chmin(dp[i+1][j+1],dp[i][j]+(x[i]==y[j]?0:r));
      chmin(dp[i+1][j],dp[i][j]+(i<n-p?e:e-s));
      chmin(dp[i][j+1],dp[i][j]+a);      
    }
  }
  return dp[n][m];
}
signed main(){
  cin.tie(0);
  ios::sync_with_stdio(0);
  string x,y;
  while(cin>>x,x!="#"){
    cin>>y;
    
    cin>>a>>e>>r>>s;
    Int n=x.size();
    Int ans=INF;
    for(Int p=0;p<n;p++)
      chmin(ans,s*p+calc(p,x,y));
    cout<<ans<<endl;          
  }
  return 0;
}
