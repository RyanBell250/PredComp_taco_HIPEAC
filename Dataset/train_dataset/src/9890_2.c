#include <bits/stdc++.h>
#define MOD 1000000007LL
using namespace std;
typedef long long ll;
typedef pair<int,int> P;

double dp[1001];
int a,b,k;
int t[35];
int sum[35];
double ct[35];
double dp2[1001][35];

double solve(int sz);
double solve2(int sz,int i);

double solve2(int sz,int i){
	if(dp2[sz][i]>=0.0)return dp2[sz][i];
	if(sz<=0){
		return 1e18;
	}
	if(i==0)return t[0]*sz+solve(sz)*sz;
	double ans=1e18;
	for(int j=1;j<=sz-1;j++){
		double val=solve(j)*j;
		val+=t[i]*j;
		val+=solve2(sz-j,i-1);
		ans=min(ans,val);
	}
	return dp2[sz][i]=ans;
}

double solve(int sz){
	if(dp[sz]>=0.0)return dp[sz];
	if(sz<=1)return 0;
	double ans=1e18;
	for(int i=1;i<=min(k,sz-1);i++){
		ans=min((double)solve2(sz,i)/sz,ans);
	}
	return (dp[sz]=ans);
}

int main(void){
	scanf("%d%d%d",&a,&b,&k);
	int n=b-a;
	for(int i=0;i<=k;i++){
		scanf("%d",&t[i]);
	}
	for(int i=0;i<=k;i++){
		sum[i+1]+=sum[i];
		sum[i+1]+=t[i];
		ct[i+1]=(double)sum[i+1]/(i+1);
	}
	for(int i=0;i<=n+1;i++){
		dp[i]=-1.0;
		for(int j=0;j<=k+1;j++){
			dp2[i][j]=-1;
		}
	}
	printf("%.10f\n",solve(n));
	return 0;
} 
