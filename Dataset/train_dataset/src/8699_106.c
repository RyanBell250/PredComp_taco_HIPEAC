#include<bits/stdc++.h>
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define SZ(x) ((int)x.size())
#define ALL(x) x.begin(),x.end()
#define L(i,u) for ( int i=head[u]; i; i=nxt[i])
#define rep(i,a,b) for ( int i=(a); i<=(b); i++)
#define per(i,a,b) for ( int i=(a); i>=(b); i--)
using namespace std;
typedef long double ld;
typedef long long ll;
typedef unsigned int ui;
typedef pair<int,int> Pii;
typedef pair<ll,ll> Pll;
typedef vector<int> Vi;
template<class T> inline void read(T &x){
	x=0; char c=getchar(); int f=1;
	while (!isdigit(c)) {if (c=='-') f=-1; c=getchar();}
	while (isdigit(c)) {x=x*10+c-'0'; c=getchar();} x*=f;
}
template<class T> T gcd(T a, T b){return !b?a:gcd(b,a%b);}
template<class T> inline void umin(T &x, T y){x=x<y?x:y;}
template<class T> inline void umax(T &x, T y){x=x>y?x:y;}
mt19937 R(chrono::system_clock().now().time_since_epoch().count());
const int N = 2020;
int n,mo,f[N*3][N];
inline void add(int &x, int y){x=x+y<mo?x+y:x+y-mo;}
int main() {
	read(n);read(mo);
	f[1][0]=1;
	rep(i,2,3*n+1)rep(j,1,min(3,i)){
		int xs=1;rep(k,i-j+1,i-1)xs=1ll*xs*(k-1)%mo;
		rep(k,0,n)if(f[i-j][k]){
			add(f[i][k+(j>=2)],1ll*f[i-j][k]*xs%mo);
		}
	}
	int res=0;rep(i,0,n)add(res,f[3*n+1][i]);
	cout<<res;
	return 0;
}
