#include <bits/stdc++.h>
using namespace std;
#define ll long long
int main() {
    ll n,k;
    cin>>n>>k;
    ll p=1000000007;
    ll ans=(1+n*(n-1))%p;
    ll dp[200001];
    ll factdp[200001];
    ll fact[200001];
    dp[0]=1;
    dp[1]=1;
    fact[0]=1;
    fact[1]=1;
    factdp[0]=1;
    factdp[1]=1;
    for(ll i=2;i<=200000;i++)
    {
        fact[i]=fact[i-1]*i%p;
        dp[i]=dp[p%i]*(p-p/i)%p;
        factdp[i]=factdp[i-1]*dp[i]%p;
    }
    for(ll m=2;m<=min(n-1,k);m++)
    {
        ans+=((fact[n])*fact[n-1]%p)*factdp[n-m]%p*factdp[n-m-1]%p*factdp[m]%p*factdp[m]%p;
    }
    cout<<ans%p;
	return 0;
}