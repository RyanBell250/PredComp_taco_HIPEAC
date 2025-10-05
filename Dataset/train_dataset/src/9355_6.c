#include <cstdio>
#include <algorithm>

using namespace std;

const int MAX_N = 105;
const int MAX_K = 100005;
const int MOD = 1000000007;

int n,k,a[MAX_N];
int dp[MAX_N][MAX_K],sum[MAX_K];

int main()
{
	scanf("%d %d",&n,&k);
	for (int i=1; i<=n; i++)
		scanf("%d",a+i);
	dp[0][0]=1;
	for (int i=1; i<=n; i++)
	{
		for (int j=1; j<=k+1; j++)
			sum[j]=(sum[j-1]+dp[i-1][j-1])%MOD;
		for (int j=0; j<=k; j++)
			dp[i][j]=(sum[j+1]-sum[max(0,j-a[i])]+MOD)%MOD;
	}
	printf("%d\n",dp[n][k]);
	return 0;
}
