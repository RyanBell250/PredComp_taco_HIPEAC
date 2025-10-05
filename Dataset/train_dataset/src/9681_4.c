#include <bits/stdc++.h>
using namespace std;

#define dump(n) cout<<"# "<<#n<<'='<<(n)<<endl
#define repi(i,a,b) for(int i=int(a);i<int(b);i++)
#define peri(i,a,b) for(int i=int(b);i-->int(a);)
#define rep(i,n) repi(i,0,n)
#define per(i,n) peri(i,0,n)
#define all(c) begin(c),end(c)
#define mp make_pair
#define mt make_tuple

typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ll> vl;
typedef vector<vl> vvl;
typedef vector<double> vd;
typedef vector<vd> vvd;
typedef vector<string> vs;

const int INF=1e9;
const int MOD=1e9+7;
const double EPS=1e-9;

template<typename T1,typename T2>
ostream& operator<<(ostream& os,const pair<T1,T2>& p){
	return os<<'('<<p.first<<','<<p.second<<')';
}
template<typename T>
ostream& operator<<(ostream& os,const vector<T>& a){
	os<<'[';
	rep(i,a.size()) os<<(i?" ":"")<<a[i];
	return os<<']';
}

int main()
{
	for(int n;cin>>n && n;){
		vi bs(n),es(n),ws(n);
		rep(i,n) cin>>bs[i]>>es[i]>>ws[i],bs[i]--;
		
		vi is(n); iota(all(is),0);
		sort(all(is),[&](int i,int j){return es[i]<es[j];});
		
		const int N=365;
		vvi dp1(N+1,vi(N+1)),dp2;
		for(int k:is){
			dp2=dp1;
			rep(i,N+1) repi(j,es[k],N+1) dp2[i][j]=max(dp2[i][j],dp1[i][bs[k]]+ws[k]);
			rep(i,N+1) repi(j,es[k],N+1) dp2[j][i]=max(dp2[j][i],dp1[bs[k]][i]+ws[k]);
			swap(dp1,dp2);
		}
		cout<<dp1[N][N]<<endl;
	}
}