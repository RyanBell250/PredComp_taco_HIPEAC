#include <bits/stdc++.h>
using namespace std;
#define F(i, s, t) for (int i = (s), _ = (t); i <= _; i ++)
#define LL long long
const int N = 2005;
const int P = 1000000007;
int n, m; LL X;
struct E {
	int x, y, z;
	friend int operator < (E A, E B) { return A.z < B.z; }
}e[N];
LL ans; int f[N], w[N], u[N];
int a, b, c, fin;
namespace Input {
	const int S = 10000000;
	char s[S], *h = s+S, *t = h;
	char nchar() {
		if (h == t) fread(s, 1, S, stdin), h = s;
		return *h ++;
	}
	LL rd() {
		LL x = 0; char c;
		do { c = nchar(); } while (! isdigit(c));
		do { x = x*10+c-'0', c = nchar(); } while (isdigit(c));
		return x;
	}
}
using Input::rd;
int Rot(int x) {
	while (f[x])
		x = f[x];
	return x;
}
void Evert(int x) {
	if (! f[x]) return;
	int t = f[x];
	Evert(t);
	f[t] = x, w[t] = w[x];
	f[x] = w[x] = 0;
}
void Link(int x, int y, int z) {
	Evert(x), f[x] = y, w[x] = z;
}
int Max(int x, int y) {
	Evert(x);
	int mx = 0;
	for (; y != x; y = f[y])
		mx = max(mx, w[y]);
	return mx;
}
int Pow(int x, int t) {
	int m = 1;
	for (; t; t >>= 1, x = (LL)x * x % P)
		if (t & 1)
			m = (LL)m * x % P;
	return m;
}
int main() {
	// freopen("c.in", "r", stdin);
	// freopen("c.out", "w", stdout);
	n = rd(), m = rd(), X = rd();
	F(i, 1, m) {
		int x = rd(), y = rd(), z = rd();
		e[i] = (E){x, y, z};
	}
	sort(e+1, e+m+1);
	F(i, 1, m) {
		int x = e[i].x, y = e[i].y, z = e[i].z;
		if (Rot(x) != Rot(y))
			ans += z, Link(x, y, z), u[i] = 1;
	}
	if (ans > X)
		return puts("0"), 0;
	if (ans == X)
		fin = (LL)(Pow(2, n-1) - 2) * Pow(2, m-n+1) % P;
	F(i, 1, m)
		if (! u[i]) {
			int x = e[i].x, y = e[i].y, z = e[i].z;
			LL t = ans - Max(x, y) + z;
			t < X ? a ++ : t == X ? b ++ : c ++;
		}
	fin = (fin + 2LL * (Pow(2, b) - 1) * Pow(2, c)) % P;
	printf("%d\n", (fin + P) % P);
	return 0;
}