#include<bits/stdc++.h>
using namespace std;
int dp[2][16][1<<16];
signed main(){
  int r,c;
  cin>>r>>c;
  string s[r];
  for(int i=0;i<r;i++) cin>>s[i];
  memset(dp,-1,sizeof(dp));
  dp[0][0][0]=0;
  int mask=(1<<c)-1;
  for(int i=0;i<r;i++){
    bool f=i%2;
    memset(dp[!f],-1,sizeof(dp[!f]));
    for(int j=0;j<c;j++){
      for(int b=0;b<(1<<c);b++){
	if(dp[f][j][b]<0) continue;
	
	char t,u;
	t=u='$';
	int y=0;
	for(int k=j-1;k>=0;k--) if((b>>k)&1) y++;
	if(j&&(b&1)) u=s[i][y-1];
	if(i){
	  int x=s[i-1].size()-(__builtin_popcountll(b)-y);
	  if(x<(int)s[i-1].size()&&((b>>(c-1))&1)) t=s[i-1][x];
	}
	if(y<(int)s[i].size()){
	  int nb=((b<<1)&mask)+1;
	  int nd=dp[f][j][b]+(t==s[i][y])*2+(u==s[i][y])*2;
	  if(j+1<c)
	    dp[f][j+1][nb]=max(dp[f][j+1][nb],nd);
	  else if(y+1==(int)s[i].size())
	    dp[!f][0][nb]=max(dp[!f][0][nb],nd);
	}
	{
	  int nb=(b<<1)&mask;
	  int nd=dp[f][j][b];
	  if(j+1<c)
	    dp[f][j+1][nb]=max(dp[f][j+1][nb],nd);
	  else if(y==(int)s[i].size())
	    dp[!f][0][nb]=max(dp[!f][0][nb],nd);
	}
      }
    }
  }
  int ans=0;
  for(int b=0;b<(1<<c);b++)
    ans=max(ans,dp[r%2][0][b]);
  cout<<ans<<endl;
  return 0;
}
