#include <bits/stdc++.h>
#define rep(i,n) for(int i=0;i<(n);i++)

using namespace std;

int sm [200002];
int tt [200002];

int main(void){
	cin.tie(0);
	ios::sync_with_stdio(false);
	int N,C;
	cin >> N >> C;
	vector<int> s(N),t(N),c(N);
	rep(i,N)cin >> s[i] >> t[i] >> c[i];
	for(int i=1;i<=C;i++){
		for(int j=0;j<200002;j++)tt[j]=0;
		for(int j=0;j<N;j++)if(c[j]==i)tt[s[j]*2-1]++,tt[t[j]*2]--;
		for(int j=1;j<200002;j++)tt[j]+=tt[j-1];
		for(int j=0;j<200002;j++)if(tt[j]>0)sm[j]++;
	}
	int mx = 0;
	for(int j=0;j<200002;j++)if(mx<sm[j])mx=sm[j];
	cout << mx << endl;
}