#include<stdio.h>
#include<algorithm>
#include<vector>
using namespace std;
int dp[400][400];
vector<pair<int,int> > v[400];
int main(){
	int a;
	while(scanf("%d",&a),a){
		for(int i=0;i<400;i++)v[i].clear();
		for(int i=0;i<a;i++){
			int x,y,z;scanf("%d%d%d",&x,&y,&z);
			x--;y--;
			v[x].push_back(make_pair(y,z));
		}
		for(int i=0;i<400;i++)for(int j=0;j<400;j++)
			dp[i][j]=0;
		dp[0][0]=0;
		for(int i=0;i<370;i++){
			for(int j=i;j<370;j++){
				dp[i+1][max(i+1,j)]=max(dp[i+1][max(i+1,j)],dp[i][j]);
				if(i==j){
					for(int k=0;k<v[i].size();k++){
						dp[i+1][v[i][k].first+1]=max(dp[i+1][v[i][k].first+1],dp[i][j]+v[i][k].second);
						for(int l=k+1;l<v[i].size();l++){
							int L=min(v[i][k].first+1,v[i][l].first+1);
							int R=max(v[i][k].first+1,v[i][l].first+1);
							dp[L][R]=max(dp[L][R],dp[i][j]+v[i][k].second+v[i][l].second);
						}
					}
				}else{
					for(int k=0;k<v[i].size();k++){
						dp[min(j,v[i][k].first+1)][max(j,v[i][k].first+1)]=max(dp[min(j,v[i][k].first+1)][max(j,v[i][k].first+1)],dp[i][j]+v[i][k].second);
					}
				}
			}
		}
		int ret=0;
		for(int i=0;i<400;i++)for(int j=0;j<400;j++)ret=max(ret,dp[i][j]);
		printf("%d\n",ret);
	}
}