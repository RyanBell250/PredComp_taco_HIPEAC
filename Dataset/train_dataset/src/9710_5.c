#include<iostream>
#include<string>
#include<cstdio>
#include<vector>
#include<cmath>
#include<algorithm>
#include<functional>
#include<iomanip>
#include<queue>
#include<ciso646>
#include<random>
#include<map>
#include<set>
#include<complex>
#include<bitset>
#include<stack>
#include<unordered_map>
using namespace std;
typedef long long ll;
typedef unsigned int ui;
const ll mod = 1000000007;
const ll INF = (ll)1000000007 * 1000000007;
typedef pair<int, int> P;
#define stop char nyaa;cin>>nyaa;
#define rep(i,n) for(int i=0;i<n;i++)
#define per(i,n) for(int i=n-1;i>=0;i--)
#define Rep(i,sta,n) for(int i=sta;i<n;i++)
#define rep1(i,n) for(int i=1;i<=n;i++)
#define per1(i,n) for(int i=n;i>=1;i--)
#define Rep1(i,sta,n) for(int i=sta;i<=n;i++)
typedef long double ld;
typedef complex<ld> Point;
const ld eps = 1e-11;
const ld pi = acos(-1.0);
typedef pair<ll, ll> LP;
typedef pair<ld, ld> LDP;
typedef unsigned long long ul;
int r, s, p;
int d[1 << 20];
int main() {
	cin >> r >> s >> p;
	rep(i,p){
		int x, y; cin >> x >> y; x--; y--;
		int dis = 0; dis += r - x;
		if (y < s) {
			dis += s - y;
		}
		else {
			dis += y - s + 1;
		}
		d[dis]++;
		
	}
	rep(i, (1 << 20)) {
		if (d[i]>1) {
			d[i + 1] += d[i] - 1; d[i] = 1;
		}
	}
	int out = 0;
	rep(i, 1 << 20) {
		if (d[i])out = i;
	}
	cout << out << endl;
	return 0;
}
