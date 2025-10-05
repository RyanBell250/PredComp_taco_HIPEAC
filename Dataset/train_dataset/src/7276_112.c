#include<bits/stdc++.h>
#define st first
#define nd second


using ll = long long;
using namespace std;
using pii = pair<int, int>;
const int N = 2e5 + 10;
const int mod = 1e9 + 7;

int way[N], fac[N], ifac[N], comp[N];
std::vector<int> gr[N];

int mul(int a, int b){
	return 1LL * a * b % mod;
}
int f_pow(int val, int idx){
	int ret = 1, pt = 0;
	while((1 <<pt) < idx){
		if(idx & (1 << pt)){
			ret = mul(ret, val);
		}
		pt++;
		val = mul(val, val);
	}
	return ret;

}
int C(int po, int n, int r){
	if(r == n) return 1;
	if(po == 1) return mul(fac[n], mul(ifac[n - r], ifac[r]));
	else return mul(ifac[n], mul(fac[n-r], fac[r]));
}


void dfs(int node, int from){
	for(auto it: gr[node]){
		if(it == from) continue;
		dfs(it, node);
		way[node] = mul(way[node] , mul(way[it] , C(1, comp[it] + comp[node], comp[it]))); 
		comp[node] += comp[it];
	}
	comp[node] ++;
	return;
}
void dis(int node, int from){

	if(node != 1){
		int fromPar = mul(way[from] ,mul(f_pow(way[node], mod - 2), C(-1, comp[from] - 1, comp[node])));
		way[node] = mul(way[node], mul(fromPar,C(1, comp[from] - 1, comp[node] - 1))); 
		comp[node] = comp[from];
	}
	for(auto it: gr[node]){
		if(it != from) dis(it, node);
	}
}
int main(){
	int n;
	scanf("%d", &n);
	for(int i = 1; i < n; i++){
		int x, y;
		scanf("%d %d", &x, &y);
		gr[x].push_back(y);
		gr[y].push_back(x);
	}
	fac[0] = 1;
	for(int i = 1; i <= n + 1; i ++){
		way[i] = 1;
		fac[i] = mul(fac[i-1],i);
	}
	ifac[n + 1]  = f_pow(fac[n+1], mod - 2), ifac[0] = 1;
	for(int i = n; i > 0; i--){
		ifac[i] = mul(i + 1, ifac[i + 1]);
	} 
	dfs(1, 0);

	dis(1, 0);
	for(int i = 1;i <= n; i++){
		printf("%d\n", way[i]);
	}

}