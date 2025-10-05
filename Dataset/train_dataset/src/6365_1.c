
#include <bits/stdc++.h>
#define EPS 1e-9
#define INF 1070000000LL
#define MOD 1000000007LL
#define fir first
#define foreach(it,X) for(auto it=(X).begin();it!=(X).end();it++)
#define ite iterator
#define mp make_pair
#define mt make_tuple
#define rep(i,n) rep2(i,0,n)
#define rep2(i,m,n) for(int i=m;i<(n);i++)
#define pb push_back
#define sec second
#define sz(x) ((int)(x).size())
using namespace std;
typedef istringstream iss;
typedef long long ll;
typedef pair<ll,ll> pi;
typedef stringstream sst;
typedef vector<ll> vi;
int m,n,obj[200];
int dp[180000];
int p3[12];
int f(int mask){
	int& res = dp[mask];
	if(res!=-1)return res;
	res = INF;
	int d[12];
	rep(i,m)d[i] = mask/p3[i]%3;
	int hit = 0;
	rep(i,n){
		int ok = 1;
		rep(j,m)if(d[j]!=2 && d[j] != (obj[i]>>j&1)){
			ok = 0;
		}
		if(ok)hit++;
		if(hit>1)break;
	}
	if(hit <= 1)return res = 0;
	rep(i,m)if(d[i] == 2){
		res = min(res, 1 + max(f(mask - 2 * p3[i]), f(mask - 1 * p3[i])));
	}
	return res;
}
int main(){
	cin.tie(0);
	ios_base::sync_with_stdio(0);
	p3[0] = 1;
	rep(i,11)p3[i+1] = p3[i] * 3;
	while(cin>>m>>n && m){
		rep(i,n){
			string s;
			cin>>s;
			obj[i] = 0;
			rep(j,m)obj[i] |= (s[j] - '0')<<j;
		}
		memset(dp,-1,sizeof(dp));
		cout<<f(p3[m]-1)<<endl;
	}
}