#include <algorithm>
#include <bitset>
#include <cassert>
#include <cctype>
#include <climits>
#include <cmath>
#include <complex>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <valarray>
#include <vector>

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

struct timer{
	time_t start;
	timer(){start=clock();}
	~timer(){cerr<<1.*(clock()-start)/CLOCKS_PER_SEC<<" secs"<<endl;}
};

typedef istringstream iss;
typedef long long ll;
typedef pair<ll,ll> pi;
typedef stringstream sst;
typedef vector<ll> vi;

int n,m,r,A[55],B[55],K[66],X[66][11],Y[66];
int V;
vi x1,x2,y;
bool dp1[55][55][600],dp2[55][55][600];
bool ok[55][55][55][55];
int dp[55][55][55][55];

void f(int n,int A[],bool dp[][55][600]){
	rep(i,2*n-1){
		dp[i][i][A[i]]=1;
	}
	rep2(len,2,n+1)rep(from,2*n-len){
		int to=from+len-1;
		rep2(cut,from,to)rep(rule,sz(x1)){
			dp[from][to][y[rule]] |=
			dp[from][cut][x1[rule]] & dp[cut+1][to][x2[rule]];
		}
	}
}

void main2(){
	rep(i,n-1)A[i+n]=A[i];
	rep(i,m-1)B[i+m]=B[i];
	V=31;
	x1.clear();
	x2.clear();
	y.clear();
	rep(i,r){
		if(K[i]==2){
			x1.pb(X[i][0]);
			x2.pb(X[i][1]);
			y.pb(Y[i]);
		}
		else rep(k,K[i]-1){
			if(k==0){
				x1.pb(X[i][0]);
				x2.pb(X[i][1]);
				y.pb(V++);
			}else if(k==K[i]-2){
				x1.pb(V-1);
				x2.pb(X[i][k+1]);
				y.pb(Y[i]);
			}else{
				x1.pb(V-1);
				x2.pb(X[i][k+1]);
				y.pb(V++);
			}
		}
	}
	
	memset(dp1,0,sizeof(dp1));
	memset(dp2,0,sizeof(dp2));
	f(n,A,dp1);
	f(m,B,dp2);
	
	memset(ok,0,sizeof(ok));
	rep(from1,2*n-1)rep2(to1,from1,2*n-1){
		rep(from2,2*m-1)rep2(to2,from2,2*m-1){
			rep(var,V){
				ok[from1][to1][from2][to2] |=
				dp1[from1][to1][var] & dp2[from2][to2][var];
			}
		}
	}
	
	rep(from1,2*n)rep2(to1,max(0,from1-1),2*n-1){
		rep(from2,2*m)rep2(to2,max(0,from2-1),2*m-1){
			dp[from1][to1][from2][to2]=
			to1==from1-1 && to2==from2-1 ? 0 : -INF;
		}
	}
	int ans=-1;
	rep2(len1,1,n+1)rep2(len2,1,m+1){
		rep(from1,2*n-len1)rep(from2,2*m-len2){
			int to1=from1+len1-1,to2=from2+len2-1;
			rep2(cut1,from1,to1+1)rep2(cut2,from2,to2+1){
				if(ok[from1][cut1][from2][cut2]){
					dp[from1][to1][from2][to2]=
					max(dp[from1][to1][from2][to2],1+dp[cut1+1][to1][cut2+1][to2]);
				}
			}
			if(len1==n && len2==m){
				ans=max(ans,dp[from1][to1][from2][to2]);
			}
		}
	}
	cout<<ans<<endl;
}

int main(){
	cin.tie(0);
	ios_base::sync_with_stdio(0);
	
	while(cin>>n>>m>>r && n){
		rep(i,n)cin>>A[i];
		rep(i,m)cin>>B[i];
		rep(i,r){
			cin>>K[i];
			rep(j,K[i])cin>>X[i][j];
			cin>>Y[i];
		}
		main2();
	}
}