#include <bits/stdc++.h>
#define MOD 1000000007
using namespace std;
int n,f[2100000];
bool c[30][30];
signed main()
{
	cin>>n;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			cin>>c[i][j];
		}
	}
	f[0]=1;
	for(int i=1;i<(1<<n);i++){
		int x=i,ans=0;
		while(x!=0){
			if(x%2==1) ans++;
			x/=2;
		}
		for(int j=1;j<=n;j++) if((i&(1<<(n-j)))&&c[n-ans+1][j]){
			f[i]+=f[i^(1<<(n-j))];
			if(f[i]>=MOD) f[i]-=MOD;
		}
	}
	cout<<f[(1<<n)-1]<<endl;
	return 0;
}
