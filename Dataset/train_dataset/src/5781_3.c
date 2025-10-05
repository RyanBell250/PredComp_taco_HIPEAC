#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll t,n;
ll sqr3(ll x){
	ll l=1,r=floor(sqrt(x));
	while(l<=r){
		ll mid=(l+r)>>1;
		ll c=mid*mid*mid;
		if (c==x) return mid;
		else if (c>x) r=mid-1;
		else l=mid+1;
	}
	return 0;
}
int main(){
	scanf("%lld",&t);
	while (t--){
		scanf("%lld",&n);
		ll ck=0;
		for (ll i=1;i*i*i<=n;i++){
			ll a=i;
			ll b=sqr3(n-i*i*i);
			if (!b) continue;
			if (a*a*a+b*b*b==n){
				printf("YES\n");
				ck=1;
				break;
			}
		}
		if (!ck) printf("NO\n");
	}
	return 0;
}
