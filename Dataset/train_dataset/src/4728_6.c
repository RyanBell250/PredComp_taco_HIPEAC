
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n,c[200],b[200],l[200],f[110][20000],q,x,pb1,pb2;
int main(){
	cin >> n;
	for(ll i=1;i<=n;i++)scanf("%lld",&c[i]);
	for(ll i=1;i<n;i++)scanf("%lld",&b[i]);
	cin >> q;
	while(q--){
		cin >> x;
		pb2=pb1=b[1];
		for(ll i=2;i<=n;i++){
			l[i]=x*i+pb2;
			pb1 += b[i];
			pb2 += pb1;
		}
		l[1]=x;
		f[0][0]=1;
		for(ll i=1;i<=n;i++){
			for(ll k=0;k<=10000;k++){
				for(ll j=0;j<=c[i];j++){
					if((k+j>=l[i]))f[i][k+j]=(f[i-1][k]+f[i][k+j])%1000000007;
				}			
			}
		}
		ll ans=0;
		for(ll k=0;k<=10000;k++){
			ans += f[n][k];
			ans %= 1000000007;
		}
		cout << ans;
	}
}