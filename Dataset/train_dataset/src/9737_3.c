#include <iostream>
#include <cstdio>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <cassert>
#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <deque>
#include <map>
#include <set>
#include <bitset>
#include <string>
#include <algorithm>
#define llint long long
#define inf 1e18
#define mod 998244353
#define rep(x, s, t) for(llint (x) = (s); (x) < (t); (x)++)
#define Rep(x, s, t) for(llint (x) = (s); (x) <= (t); (x)++)
using namespace std;
typedef pair<llint, llint> P;
string s, t;
string a[105];
llint beki[1005];
string ans;
string x, y;
vector<llint> vec, vec2;
llint gethash(string &s)
{
	llint hash = 0;
	for(int j = 0; j < 1000; j++){
		if(s[j] == '1') hash ^= beki[j];
	}
	return hash;
}
void get(string &s, vector<llint> &vec)
{
	for(int i = 0; i < 100; i++){
		llint h = 0;
		for(int j = 0; j < 30; j++){
			llint c = s[i*30+j]-'0';
			h |= c<<j;
		}
		vec.push_back(h);
	}
}
int main(void)
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	beki[0] = 1;
	for(int i = 1; i < 1005; i++) beki[i] = beki[i-1] * 2 % mod;
	cin >> s;
	if(s == "Alice" || s == "Bob"){
		for(int i = 1; i <= 100; i++) cin >> a[i];
		for(int i = 1; i <= 100; i++){
			llint hash = gethash(a[i]);
			for(int j = 0; j < 30; j++){
				ans += (char)(((hash >> j)&1) + '0');
			}
		}
		cout << ans << endl;
		return 0;
	}
	else{
		cin >> x >> y;
		get(x, vec), get(y, vec2);
		for(int i = 1; i <= 100; i++){
		cin >> t;
			llint hash = gethash(t);
			for(int j = 0; j < vec.size(); j++){
				for(int k = 0; k < vec2.size(); k++){
					if((vec[j]^vec2[k]^hash) == 0){
						cout << j+1 << " " << k+1 << endl;
						goto end;
					}
				}
			}
			end:;
		}
	}
	return 0;
}
