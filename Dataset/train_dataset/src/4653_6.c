#include <iostream>
#include <map>
#include <cstring>
#include <vector>
#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;

int n,m;

vector<int> g[100010],rg[100010];
vector< pair<int,int> > e;

int dp[100010];
int f[100010];
vector<int> depth[100010];

map< pair<int,int> , int > pos;
int main(){
	cin >> n >> m;
	for(int i = 0; i < m; i++){
		int a,b;
		cin >> a >> b;
		g[a].push_back(b);
		rg[b].push_back(a);
		pos[make_pair(a,b)] = i;
	}
	
	for(int i = 1; i <= n; i++){
		g[0].push_back(i);
		rg[i].push_back(0);
	}
	
	for(int i = 0; i <= n; i++)
		for(int j = 0; j < g[i].size(); j++)
			dp[g[i][j]] = max(dp[g[i][j]],dp[i]+1);
	
	int maximum = *max_element(dp,dp+100010);
	
	for(int i = n; i >= 0; i--){
		if(maximum == dp[i]) f[i] = 1;
		else if(f[i] == 0) continue;
		for(int j = 0; j < rg[i].size(); j++){
			if(dp[rg[i][j]]+1 == dp[i]){
				f[rg[i][j]] |= f[i];
				e.push_back(make_pair(rg[i][j],i));
			}
		}
	}
	for(int i = 0; i < e.size(); i++){
		depth[dp[e[i].first]].push_back(pos[make_pair(e[i].first,e[i].second)]);
	}
	vector<int> ans;
	for(int i = 1 ; i < 100010 ; i++){
		if( depth[i].size() == 1 ){
			ans.push_back(depth[i][0]+1);
		}
	}
	sort(ans.begin(),ans.end());
	for(int i = 0 ; i < ans.size() ; i++)
		cout << ans[i] << endl;
	if( ans.size() == 0 ) cout << -1 << endl;
}