#include <bits/stdc++.h>
using namespace std;
#define db(x) cerr << #x << "=" << x << endl
#define db2(x, y) cerr << #x << "=" << x << "," << #y << "=" << y << endl
#define db3(x, y, z) cerr << #x << "=" << x << "," << #y << "=" << y << "," << #z << "=" << z << endl
#define dbv(v) cerr << #v << "="; for (auto _x : v) cerr << _x << ", "; cerr << endl
#define dba(a, n) cerr << #a << "="; for (int _i = 0; _i < (n); ++_i) cerr << a[_i] << ", "; cerr << endl
template <typename A, typename B>
ostream& operator<<(ostream& os, const pair<A, B>& x) {
	return os << "(" << x.first << "," << x.second << ")";
}
typedef long long ll;
typedef long double ld;
const int MOD = 1000000007;
struct Mint {
	int val;
	Mint() { val = 0; }
	Mint(const ll& x) {
		val = (-MOD <= x && x < MOD) ? x : x % MOD;
		if (val < 0) val += MOD;
	}
	template <typename U>
	explicit operator U() const { return (U)val; }
	friend bool operator==(const Mint& a, const Mint& b) { return a.val == b.val; }
	friend bool operator!=(const Mint& a, const Mint& b) { return !(a == b); }
	friend bool operator<(const Mint& a, const Mint& b) { return a.val < b.val; }
	Mint& operator+=(const Mint& m) { if ((val += m.val) >= MOD) val -= MOD; return *this; }
	Mint& operator-=(const Mint& m) { if ((val -= m.val) < 0) val += MOD; return *this; }
	Mint& operator*=(const Mint& m) { val = (ll)val * m.val % MOD; return *this; }
	friend Mint modex(Mint a, ll p) {
		assert(p >= 0);
		Mint ans = 1;
		for (; p; p >>= 1, a *= a) if (p & 1) ans *= a;
		return ans;
	}
	Mint& operator/=(const Mint& m) { return *this *= modex(m, MOD - 2); }
	Mint& operator++() { return *this += 1; }
	Mint& operator--() { return *this -= 1; }
	Mint operator++(int) { Mint result(*this); *this += 1; return result; }
	Mint operator--(int) { Mint result(*this); *this -= 1; return result; }
	Mint operator-() const { return Mint(-val); }
	friend Mint operator+(Mint a, const Mint& b) { return a += b; }
	friend Mint operator-(Mint a, const Mint& b) { return a -= b; }
	friend Mint operator*(Mint a, const Mint& b) { return a *= b; }
	friend Mint operator/(Mint a, const Mint& b) { return a /= b; }
	friend ostream& operator<<(ostream& os, const Mint& x) { return os << x.val; }
};
int main() {
	int n, A, B;
	scanf("%d%d%d", &n, &A, &B);
	if (A > B) swap(A, B);
	vector<Mint> H(n + 3), I(n + 1, 1);
	vector<vector<Mint>> F(n + 1, vector<Mint>(2));
	vector<vector<Mint>> G(n + 1, vector<Mint>(2));
	for (int i = 1; i <= n; ++i) {
		I[i] = I[i - 1];
		for (int j = A; j <= i; ++j) I[i] += i == j ? 1 : I[i - j - 1];
	}
	for (int i = 1; i <= n + 2; ++i) {
		H[i] = i == 1 ? 1 : I[i - 2];
	}
	G[0][0] = F[0][0] = 1;
	for (int i = 1; i <= n; ++i) {
		for (int p = 0; p < 2; ++p) {
			for (int j = 1; j <= min(i, A - 1); ++j) {
				F[i][p] += G[i - j][p];
			}
		}
		for (int j = 1; j <= i; ++j) {
			int jj = j;
			if (i == j) ++jj;
			if (i == n) ++jj;
			Mint h = H[jj];
			if (j < B) G[i][0] += h * F[i - j][0];
			G[i][1] += h * F[i - j][1];
			if (j >= B) G[i][1] += h * F[i - j][0];
		}
	}
	Mint ans = F[n][1] + G[n][1];
	printf("%d\n", ans.val);
}