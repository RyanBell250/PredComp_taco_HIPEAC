#include <bits/stdc++.h>
#define MOD 1000000007LL
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int r,c;
string str[130];
int dp[2][1<<17];
vector<int> pat[17];
int main(void){
	scanf("%d%d",&r,&c);
	for(int i=0;i<r;i++){
		cin >> str[i];
	}
	int now=1,prev=0;
	memset(dp,-1,sizeof(dp));
	dp[0][0]=0;
	for(int i=0;i<r;i++){
		for(int j=0;j<c;j++){
			for(int bit=0;bit<(1<<c);bit++){
				if(dp[prev][bit]>=0){
					if(j==0 && i>0){
						if(__builtin_popcount(bit)!=(int)str[i-1].size())continue;
					}
					int nbit=bit<<1;
					bool flag=false;
					if(nbit>=(1<<c)){
						nbit-=(1<<c);
						flag=true;
					}
					dp[now][nbit]=max(dp[now][nbit],dp[prev][bit]);
					int sc=0;
					int cnt=0;
					for(int k=0;k<j;k++){
						if(bit>>k & 1)cnt++;
					}
					if(j>0 && (bit>>0 & 1)){
						if(cnt>0 && str[i][cnt-1]==str[i][cnt])sc++;
					}
					if(flag){
						int v=__builtin_popcount(bit)-cnt;
						if(v>0){
							if(str[i-1][(int)str[i-1].size()-v]==str[i][cnt])sc++;
						}
					}
					dp[now][nbit+1]=max(dp[now][nbit+1],dp[prev][bit]+sc);
				}
			}
			swap(now,prev);
			memset(dp[now],-1,sizeof(dp[now]));
		}
	}
	int ans=0;
	for(int i=0;i<(1<<c);i++){
		if(__builtin_popcount(i)==(int)str[r-1].size()){
			ans=max(ans,dp[prev][i]);
		}
	}
	printf("%d\n",ans*2);
	return 0;
}
