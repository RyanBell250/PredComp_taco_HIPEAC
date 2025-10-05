#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod=998244353;
#define inf 0x3f3f3f3f
string s;
ll dp[2000050][3][3];
ll qpow(ll n,ll k)
{
	ll ans=1;
	while(k)
	{
		if(k&1)
		ans=ans*n%mod;
		n=n*n%mod;
		k>>=1;
	}
	return ans;
}
int main()
{
	cin>>s;
	int len=s.size();
	if(len==1)
	{
		cout<<1<<endl;
		return 0;
	}
	else if(len==3)
	{
	 if(s[0]!=s[1]&&s[1]!=s[2]&&s[0]!=s[2])
	 {
	 	cout<<3;
	 	return 0;
	 }
	}
	bool flag=1;
	for(int i=0;i<len-1;i++)
	{
		if(s[i]!=s[i+1])
		{
			flag=0;
			break;
		}
	}
	if(flag)
	{
		cout<<1;
		return 0;
	}
	for(int i=0;i<3;i++)
	dp[1][i][i]=1;
	for(int i=1;i<len;i++)
	{
		for(int j=0;j<3;j++)
		{
			for(int k=0;k<3;k++)
			{
				for(int l=0;l<3;l++)
				{
					if(k==l)continue;
					int ss=j+l;
					ss%=3;
					dp[i+1][l][ss]+=dp[i][k][j];
					dp[i+1][l][ss]%=mod;
				}
			}
		}
	}
	ll ans=qpow(3,len-1);
	int tmp=0;
	flag=1;
	for(int i=0;i<len;i++)
	{
		tmp+=s[i]-'a';
		if(i)
		{
			flag&=(s[i]!=s[i-1]);
		}
	 } 
	 if(flag)
	 ans++;
	 tmp%=3;
	 for(int i=0;i<3;i++)
	 {
	 	ans-=dp[len][i][tmp];
	 	while(ans<0)
	 	ans+=mod;
	 }
	 cout<<ans%mod<<endl;
	return 0;
}
