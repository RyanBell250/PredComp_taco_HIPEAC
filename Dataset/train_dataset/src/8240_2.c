#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define pll pair<ll,ll> 

const ll N=5e5+5;
const ll mod=1e9+7;
vector<ll> F(N, 0);

void fact(ll n){
	F.assign(n, 0);
	F[0]=F[1]=1;
	for(ll i=2;i<n;i++)
		F[i]=(i*F[i-1])%mod;
}

ll mpow(ll a, ll b){
	ll x=1;
	while(b>0){
		if(b&1)
			x=(x*a)%mod;
		b>>=1;
		a=(a*a)%mod;
	}
	return x%mod;
}
ll P(ll n, ll r){
	ll x=F[n];
	ll y=F[n-r];
	y=mpow(y, mod-2);
	return (x*y)%mod;
}

ll C(ll n, ll r){
	ll x=P(n, r);
	ll y=F[r];
	y=mpow(y, mod-2);
	return (x*y)%mod;
}


int main(){
	
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	
	ll n, m;
	cin>>n>>m;
	fact(m+1);
	ll ans=0;
	for(ll i=0;i<=n;i++){
		if(i%2==0){
			ans+=P(m-i, n-i)*C(n, i);
			ans%=mod;
		} else{
			ans-=P(m-i,n-i)*C(n, i);
			ans=(ans%mod+mod)%mod;
		}
	}
	ans=ans*P(m, n)%mod;
	cout<<ans<<endl;
}


