#include <bits/stdc++.h>
using namespace std;
#define rep(i,n) for(int i=0;i<(int)(n);i++)
typedef long long ll;
int main() {
  int h,w,k,cnt,ans=0;
  cin>>h>>w>>k;
  vector<string> c(h);
  rep(i,h)cin>>c[i];
  rep(ii,1<<h)rep(jj,1<<w){
    cnt=0;
    rep(i,h)rep(j,w){
      if((ii>>i)&1)continue;
      if((jj>>j)&1)continue;
      if(c[i][j]=='#')cnt++;
    }
    if(cnt==k)ans++;
  }
  cout<<ans;
}