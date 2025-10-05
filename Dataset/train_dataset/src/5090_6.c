#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a);i<(b);i++)
#define RFOR(i,a,b) for(int i=(b) - 1;i>=(a);i--)
#define REP(i,n) for(int i=0;i<(n);i++)
#define RREP(i,n) for(int i=n-1;i>=0;i--)

#define PB push_back
#define INF INT_MAX/3
#define ALL(a) (a).begin(),(a).end()
#define RALL(a) (a).rbegin(),(a).rend()
#define CLR(a) memset(a,0,sizeof(a))

typedef long long int ll;

using namespace std;

bool istr(vector<int> b){
    REP(i,b.size()){
	if(b[i] != (i+1)) return false;
    }
    return true;
}

int main(){
    while(true){
	int n;
	vector<int> b;
	cin >> n;
	if(n == 0) break;
	REP(i,n){
	    int temp;
	    cin >> temp;
	    b.PB(temp);
	}
	int ans = 0;
	while(!istr(b)){
	    int cnt = 0;
	    ans++;
	    if(ans >= 10000) break;
	    REP(i,b.size()) {
		b[i]--;
		cnt++;
	    }
	    RREP(i,b.size()) {
		if(b[i] == 0) b.erase(b.begin()+i);
	    }
	    b.PB(cnt);
	}
	if(ans >= 10000) ans = -1;
	cout << ans << endl;
    }
    return 0;
}