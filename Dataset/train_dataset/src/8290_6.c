#include<bits/stdc++.h>
using namespace std;
const int N = 110;
typedef long long ll;
char s[N];ll k;
int l[N];
int n;
ll ans=0;
int main()
{
	scanf("%s",s+1);cin >> k;
	n=strlen(s+1);
	for(int u=1,v;u<=n;u=v+1){
		v=u;while(v+1<=n&&s[v+1]==s[u])++v;
		l[u] = l[v] = v-u+1;
		ans += k*(l[u]/2);
	}
	if(s[1]==s[n]){
		ans-=k*(l[1]/2)+k*(l[n]/2);
		ans+= l[1]/2+l[n]/2+(k-1)*((l[1]+l[n])/2);
	}
	if(l[1]==n){
		ans=n*k/2;
	}
	cout << ans << endl;
}
