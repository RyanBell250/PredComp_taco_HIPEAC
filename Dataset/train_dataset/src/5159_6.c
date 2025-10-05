#include<bits/stdc++.h>
using namespace std;
#define int long long
#define LEN 86400
signed main(){
  int n;
  cin>>n;
  int s[LEN*2+1];
  memset(s,0,sizeof(s));
  int t=0;
  for(int i=0;i<n;i++){
    int a,b;
    cin>>a>>b;
    (t+=a)%=LEN;
    s[t]++;
    s[t+LEN]++;
    (t+=b)%=LEN;
  }
  for(int i=1;i<LEN*2+1;i++) s[i]+=s[i-1];
  int ans=s[10800];
  for(int i=1;i<LEN;i++){
    ans=max(ans,s[i+10800]-s[i-1]);
  }
  cout<<ans<<endl;
  return 0;
}
