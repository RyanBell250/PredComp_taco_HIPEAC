#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>
#include <map>
#include <string.h>
#include <cmath>

using namespace std;
typedef long long i64;
typedef long double ld;
typedef pair<int,int> P;
#define rep(i,s,e) for(int (i) = (s);(i) <= (e);++(i))

int h,w;

int fie[2020][2020];
vector<vector<int>> xs(2020,vector<int>(2020,0));
int main(){
	cin >> h >> w;
	rep(i,1,h){
		string s;
		cin >> s;
		rep(j,1,w){
			if(s[j - 1] == '#'){
				fie[i][j] = 1;
			}
		}
	}
	rep(i,1,h - 1)rep(j,1,w - 1){
		int cou = 0;
		rep(dx,0,1)rep(dy,0,1) cou += fie[i + dx][j + dy];
		if(cou != 3 && cou != 1){
			if(i == 1) xs[i][j] = 1;
			else xs[i][j] = xs[i - 1][j] + 1;
		}
	}

	int ans = max(h,w);
	rep(i,1,h - 1){
		stack<P> s;
		rep(j,1,w - 1){
			int lj = j;
			while(!s.empty() && s.top().first > xs[i][j]){
				ans = max(ans , (s.top().first + 1) * (j - s.top().second + 1));
				lj = s.top().second;
				s.pop();
			}
			if(xs[i][j]) s.emplace(xs[i][j],lj);
		}
		while(!s.empty()){
			ans = max(ans, (s.top().first + 1) * (w - s.top().second + 1));
			s.pop();
		}
	}

	cout << ans << endl;
}
