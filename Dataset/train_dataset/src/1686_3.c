#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod=1e9+7;
int main(){
 int n;
 cin>>n;
 vector<vector<int>> a(n,vector<int>(n));
 for(int i=0;i<n;i++){
  for(int j=0;j<n;j++){
   cin>>a[i][j];
  }
 }
 vector<int> dp(1<<n);
 dp[0]=1;
 for(int mask=0;mask<(1<<n)-1;mask++){
  int i=__builtin_popcount(mask);
  for(int j=0;j<n;j++){
   if(a[i][j]&&!(mask&(1<<j))){
    int m2=mask^(1<<j);
    dp[m2]+=dp[mask];
    if(dp[m2]>=mod) dp[m2]-=mod;
   }
  }
 }
 cout<<dp[(1<<n)-1]<<endl;
 return 0;
}
