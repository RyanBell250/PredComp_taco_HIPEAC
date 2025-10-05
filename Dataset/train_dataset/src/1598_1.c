#include <bits/stdc++.h>

using namespace std;

inline int toInt(string s) {int v; istringstream sin(s);sin>>v;return v;}
template<class T> inline string toString(T x) {ostringstream sout;sout<<x;return sout.str();}
template<class T> inline T sqr(T x) {return x*x;}

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<string> vs;
typedef pair<int, int> pii;
typedef long long ll;

#define all(a)  (a).begin(),(a).end()
#define rall(a) (a).rbegin(), (a).rend()
#define pb push_back
#define mp make_pair
#define each(i,c) for(typeof((c).begin()) i=(c).begin(); i!=(c).end(); ++i)
#define exist(s,e) ((s).find(e)!=(s).end())
#define range(i,a,b) for(int i=(a);i<(b);++i)
#define rep(i,n)  range(i,0,n)
#define clr(a,b) memset((a), (b) ,sizeof(a))
#define dump(x)  cerr << #x << " = " << (x) << endl;
#define debug(x) cerr << #x << " = " << (x) << " (L" << __LINE__ << ")" << " " << __FILE__ << endl;

const double eps = 1e-10;
const double pi  = acos(-1.0);
const ll INF =1LL << 62;
const int inf =1 << 29;

int dp[1<<16];

int main(void){
	int n;
	while(cin >> n){
		if(n==0)
			break;
		rep(i,1<<16) dp[i]=0;
		rep(i,n){
			int m,l,mask=0;
			cin >> m >> l;
			rep(j,m){
				int s,e;
				cin >> s >> e;
				s-=6,e-=6;
				for(int k=s;k<e;++k)
					mask|=(1<<k);
			}
			rep(j,1<<16) if((j&mask)==0)
				dp[j|mask]=max(dp[j|mask],dp[j]+l);
		}
		int ans=0;
		rep(i,1<<16) ans=max(ans,dp[i]);
		cout << ans << endl;
	}
	return 0;
}