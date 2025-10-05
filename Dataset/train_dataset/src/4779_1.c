#include<bits/stdc++.h>
using namespace std;
using Int = long long;
template<typename T1,typename T2> inline void chmin(T1 &a,T2 b){if(a>b) a=b;}
template<typename T1,typename T2> inline void chmax(T1 &a,T2 b){if(a<b) a=b;}
signed main(){
  Int n,l;
  cin>>n>>l;
  vector<Int> v(n),w(n),m(n);
  for(Int i=0;i<n;i++)
    cin>>v[i]>>w[i]>>m[i];
  const Int x=50;
  const Int INF = 1e15;
  vector<Int> dp(n*x*x+1,INF);
  dp[0]=0;
  for(Int i=0;i<n;i++){
    Int s=min(m[i],x);
    m[i]-=s;
    for(Int k=1;;k<<=1){
      chmin(k,s);
      if(!k) break;
      for(Int j=n*x*x;j>=0;j--)
	if(j+k*v[i]<=n*x*x) chmin(dp[j+k*v[i]],dp[j]+k*w[i]);	
      s-=k;      
    }
  }
  vector<Int> ord(n);
  iota(ord.begin(),ord.end(),0);
  sort(ord.begin(),ord.end(),[&](Int a,Int b){
      return v[a]*w[b]>v[b]*w[a];
    });
  Int ans=0;
  for(Int j=0;j<=n*x*x;j++){
    Int lim=l-dp[j];
    if(lim<0) continue;
    Int res=j;
    for(Int i=0;i<n;i++){
      Int k=ord[i];
      Int c=min(m[k],lim/w[k]);
      lim-=w[k]*c;
      res+=v[k]*c;      
    }
    chmax(ans,res);
  }
  cout<<ans<<endl;
  return 0;
}
