#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5 + 5;
typedef long long ll;
template <typename T> void chkmax(T &x, T y) {x = max(x, y); }
template <typename T> void chkmin(T &x, T y) {x = min(x, y); } 
template <typename T> void read(T &x) {
	x = 0; int f = 1;
	char c = getchar();
	for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
	for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
	x *= f;
}
vector <int> a[MAXN];
int n, f[MAXN], p[MAXN], s[MAXN], ans[MAXN];
void dfs(int pos, int fa) {
	f[pos] = fa;
	for (auto x : a[pos])
		if (x != fa) dfs(x, pos);
}
int find(int x) {
	if (p[x] == x) return x;
	else return p[x] = find(p[x]);
}
void work(int pos, int fa, int sum) {
	vector <int> mem;
	priority_queue <int, vector <int>, greater <int>> Heap;
	while (!Heap.empty()) Heap.pop(); Heap.push(pos);
	while (!Heap.empty() && (Heap.top() == pos || Heap.top() <= fa)) {
		int tmp = Heap.top(); Heap.pop(), sum++;
		for (auto x : a[tmp]) if (f[x] == tmp) Heap.push(x), mem.push_back(x), p[x] = (tmp == pos) ? x : tmp;
	}
	ans[pos] = sum;
	while (!Heap.empty() && (Heap.top() == pos || Heap.top() <= pos)) {
		int tmp = Heap.top(); Heap.pop(), s[find(tmp)]++;
		for (auto x : a[tmp]) if (f[x] == tmp) Heap.push(x), mem.push_back(x), p[x] = tmp;
	}
	for (auto x : mem) ans[x] = sum + s[find(x)];
	while (!Heap.empty()) {
		work(Heap.top(), pos, sum + s[find(Heap.top())]);
		Heap.pop();
	}
}
int main() {
	read(n);
	for (int i = 1; i <= n - 1; i++) {
		int x, y; read(x), read(y);
		a[x].push_back(y);
		a[y].push_back(x);
	}
	dfs(1, 0);
	for (auto x : a[1])
		work(x, 1, 0);
	for (int i = 2; i <= n; i++)
		printf("%d ", ans[i]);
	return 0;
}
