#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long int lli;
const lli mod = 1e9 +7;
lli ExGCD(lli a, lli b, lli &x, lli &y){
    lli d=a;
    x=1; y=0;
    if(b!=0){ d=ExGCD(b, a%b, y, x); y-=a/b*x; }
    return d;
}
lli inverse(lli a, lli mod){
	lli x,y;
	ExGCD(a, mod, x, y);
	return x>0? x: mod+x;
}
int main(){
	while(1){
		lli n,d,x;
		cin >> n >> d >> x;
		if(n==0) break;
		vector<lli> dp(n+1, 0), num(n+1, 0);
		dp[n] = 1;
		for(int i=1; i<=n; i++){
			vector<lli> ndp(n+1, 0);
			for(int j=n-1; j>=0; j--){
				ndp[j] = dp[j+1] +ndp[j+1];
				if(j+x < n+1){
					ndp[j] -= dp[j+x];
				}
				ndp[j] = (ndp[j] +mod)%mod;
			}
			num[i] = ndp[0];
			dp = ndp;
		}
		lli ans = 0;
		lli comb = 1;
		for(lli i=1; i<=n; i++){
			lli rate = (d-i+1)%mod *inverse(i, mod) %mod;
			comb = comb*rate %mod;
			ans += comb*num[i] %mod;
		}
		ans %= mod;
		cout << ans << endl;
	}
	return 0;
}
