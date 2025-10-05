#include "bits/stdc++.h"
using namespace std;


const int mod = 1000000009;
struct Mod {
public:
	int num;
	Mod() : Mod(0) { ; }
	Mod(long long int n) : num((n % mod + mod) % mod) {
		static_assert(mod<INT_MAX / 2, "mod is too big, please make num 'long long int' from 'int'");
	}
	Mod(int n) : Mod(static_cast<long long int>(n)) { ; }
	operator int() { return num; }
};

Mod operator+(const Mod a, const Mod b) { return Mod((a.num + b.num) % mod); }
Mod operator+(const long long int a, const Mod b) { return Mod(a) + b; }
Mod operator+(const Mod a, const long long int  b) { return b + a; }
Mod operator++(Mod &a) { return a + Mod(1); }
Mod operator-(const Mod a, const Mod b) { return Mod((mod + a.num - b.num) % mod); }
Mod operator-(const long long int a, const Mod b) { return Mod(a) - b; }
Mod operator--(Mod &a) { return a - Mod(1); }
Mod operator*(const Mod a, const Mod b) { return Mod(((long long)a.num * b.num) % mod); }
Mod operator*(const long long int a, const Mod b) { return Mod(a)*b; }
Mod operator*(const Mod a, const long long int b) { return Mod(b)*a; }
Mod operator*(const Mod a, const int b) { return Mod(b)*a; }
Mod operator+=(Mod &a, const Mod b) { return a = a + b; }
Mod operator+=(long long int &a, const Mod b) { return a = a + b; }
Mod operator-=(Mod &a, const Mod b) { return a = a - b; }
Mod operator-=(long long int &a, const Mod b) { return a = a - b; }
Mod operator*=(Mod &a, const Mod b) { return a = a * b; }
Mod operator*=(long long int &a, const Mod b) { return a = a * b; }
Mod operator*=(Mod& a, const long long int &b) { return a = a * b; }
Mod operator^(const Mod a, const int n) {
	if (n == 0) return Mod(1);
	Mod res = (a * a) ^ (n / 2);
	if (n % 2) res = res * a;
	return res;
}
Mod mod_pow(const Mod a, const int n) {
	if (n == 0) return Mod(1);
	Mod res = mod_pow((a * a), (n / 2));
	if (n % 2) res = res * a;
	return res;
}
Mod inv(const Mod a) { return a ^ (mod - 2); }
Mod operator/(const Mod a, const Mod b) {
	assert(b.num != 0);
	return a * inv(b);
}
Mod operator/(const long long int a, const Mod b) {
	return Mod(a) / b;
}
Mod operator/=(Mod &a, const Mod b) {
	return a = a / b;
}

#define MAX_MOD_N 3024000

Mod fact[MAX_MOD_N], factinv[MAX_MOD_N];
void init(const int amax=MAX_MOD_N) {
	fact[0] = Mod(1); factinv[0] = 1;
	for (int i = 0; i < amax - 1; ++i) {
		fact[i + 1] = fact[i] * Mod(i + 1);
		factinv[i + 1] = factinv[i] / Mod(i + 1);
	}
}
Mod comb(const int a, const int b) {
	assert(a >= b);
	assert(a >= 0 && b >= 0);
	return fact[a] * factinv[b] * factinv[a - b];
}

struct rel {
	int a;
	int b;
	int love;
};

struct UnionFind {
	vector<int> data;
	UnionFind(int size) : data(size, -1) { }
	bool unionSet(int x, int y) {
		x = root(x); y = root(y);
		if (x != y) {
			if (data[y] < data[x]) swap(x, y);
			data[x] += data[y]; data[y] = x;
		}
		return x != y;
	}
	bool findSet(int x, int y) {
		return root(x) == root(y);
	}
	int root(int x) {
		return data[x] < 0 ? x : data[x] = root(data[x]);
	}
	int size(int x) {
		return -data[root(x)];
	}
};
vector<Mod>dp(1e6 + 10);
Mod getrest(const int rest) {
	if (rest < 0) {
		return 0;
	}
	else {
		if (rest % 3) {
			assert(false);
			return 0;
		}
		else {
			return dp[rest/3];
		}
	}
}
int N, M;
Mod getans(const map<int,int>&mp) {
	vector<int>v;

	Mod ans = 1;
	for (auto m : mp) {
		if (m.second >= 4)return 0;
		else if(m.second==1){
		}
		else {
			v.emplace_back(m.second);
		}
	}
	int rest = 3 * N - accumulate(v.begin(), v.end(),0);
	if (N < v.size())return 0;
	for (auto n : v) {
		ans *= comb(rest, 3 - n);
		rest -= (3-n);
	}
	ans *= getrest(rest);
	return ans;
}
int main() {
	dp[0] = 1;
	cin >> N >> M;

	for (int i = 1; i <= N+1; ++i) {
		dp[i] = dp[i - 1] * Mod(3 * i - 1)*Mod(3 * i - 2) / Mod(2);
	}
	init(3*N+10);
	vector<rel>rels;
	vector<rel>hates;
	set<int>aset;
	for (int i = 0; i < M; ++i) {
		int a, b, c; cin >> a >> b >> c;
		c = !c;
		a--; b--;
		aset.emplace(a);
		aset.emplace(b);
		rels.push_back(rel{ a,b,c });
	}
	map<int, int>mp;
	int n = 0;
	for (auto s : aset) {
		mp[s] = n;
		n++;
	}
	for (auto&r : rels) {
		r.a = mp[r.a];
		r.b = mp[r.b];
	}
	UnionFind uf(aset.size());
	for (int i = 0; i < M; ++i) {
		if (rels[i].love) {
			uf.unionSet(rels[i].a, rels[i].b);
		}
		else {
			hates.emplace_back(rels[i]);
		}
	}
	Mod ans = 0;
	for (int i = 0; i < (1<<hates.size()); ++i) {
		UnionFind nowuf(uf);
		bitset<18>bs(i);
		for (int j = 0; j < hates.size(); ++j) {
			
			if (bs[j]) {
				nowuf.unionSet(hates[j].a, hates[j].b);
			}
		}
		map<int, int>lovemp;
		for (int j = 0; j < aset.size(); ++j) {
			lovemp[nowuf.root(j)]++;
		}
		if (bs.count() % 2) {
			ans -= getans(lovemp);
		}
		else {
			ans += getans(lovemp);
		}
	}
	cout << ans << endl;
	return 0;
}