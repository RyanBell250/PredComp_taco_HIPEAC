#include <bits/stdc++.h>
#define mp make_pair
#define mt make_tuple
#define fi first
#define se second
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define forn(i, n) for (int i = 0; i < (int)(n); ++i)
#define for1(i, n) for (int i = 1; i <= (int)(n); ++i)
#define ford(i, n) for (int i = (int)(n) - 1; i >= 0; --i)
#define fore(i, a, b) for (int i = (int)(a); i <= (int)(b); ++i)
#define deb(x) cout<<#x<<" "<<endl;
using namespace std;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<pii> vpi;
typedef vector<vi> vvi;
typedef long long ll;
typedef vector<ll> vll;
typedef vector<vll> vvll;
typedef pair<ll, ll> pll;
typedef double ld;
template<class T> bool uin(T &a, T b) { return a > b ? (a = b, true) : false; }
template<class T> bool uax(T &a, T b) { return a < b ? (a = b, true) : false; }

void solve(){
	int n;cin>>n;
	vi a(n);
	forn(i,n){
		cin>>a[i];
	}
	vi extra;
	set<int> s;
	forn(i,n){
		if(s.find(a[i])!=s.end()){
			extra.pb(a[i]);
		}
		else{
			s.insert(a[i]);
		}
	}
	for(auto i:s){
		cout<<i<<" ";
	}
	sort(extra.begin(),extra.end());
	forn(i,extra.size()){
		cout<<extra[i]<<" ";
	}
	cout<<'\n';
}
int main(){
	ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
	#ifndef ONLINE_JUDGE
	freopen("E:\\input-output\\input.txt","r",stdin);
	freopen("E:\\input-output\\output.txt","w",stdout);
	#endif
	int t=1;
	cin>>t;
	while(t--){
		solve();
	}
}
