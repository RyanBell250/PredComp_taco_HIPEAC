#include "bits/stdc++.h"
using namespace std;
typedef pair<int,int> P;
P comp(P lhs,P rhs)
{
	if(lhs.first>rhs.first)
		return lhs;
	else if(lhs.first==rhs.first && lhs.second<rhs.second)
		return lhs;
	else
		return rhs;	
}
P dp[101][50001]; 
int m[100]; 
P pay1000[100]; 
P adjust[100]; 
int main()
{
	while(1)
	{
		int n;
		cin>>n;
		if(n==0)
			break;
		for(int i=0;i<n;i++)
		{
			cin>>m[i];
			int p=(7000-m[i])%1000;
			if(p>=500)
				pay1000[i]=P(1,p-500);
			else
				pay1000[i]=P(0,p);
			p=(m[i]+1000)%1000;
			if(p!=0)
				adjust[i]=P(1,(p+500)%1000);
			else
				adjust[i]=P(1,500);
		}
		fill(dp[0],dp[101],P(-1,-1));
		dp[0][0]=P(0,0);
		for(int i=1;i<n+1;i++)
		{
			for(int j=0;j<50001;j++)
			{
				if(dp[i-1][j]!=P(-1,-1))
				{
					dp[i][j]=comp(dp[i][j],dp[i-1][j]);
					if(j>=adjust[i-1].second)
					{
						dp[i][j-adjust[i-1].second]=comp(dp[i][j-adjust[i-1].second], 
							P(dp[i-1][j].first+adjust[i-1].first, dp[i-1][j].second+m[i-1]));
					}
					dp[i][j+pay1000[i-1].second]=comp(dp[i][j+pay1000[i-1].second],
						P(dp[i-1][j].first+pay1000[i-1].first, dp[i-1][j].second+m[i-1]));
				}
			}
		}
		P ans=P(0,0);
		for(int i=0;i<50001;i++)
			ans=comp(dp[n][i],ans);
		cout<<ans.first<<" "<<ans.second<<endl;
	}
	return 0;
}
