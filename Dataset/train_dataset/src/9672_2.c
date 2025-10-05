#include <cstdio>
#include <vector>
using namespace std;


typedef long long int int64;
int mod = 1000000007;


pair<int, int> extgcd(int a, int b)
{
	if(b == 0)
		return {1, 0};

	const auto res = extgcd(b, a % b);
	const int xd = res.first;
	const int yd = res.second;
	const int x = yd;
	const int y = xd - a / b * yd;
	return {x, y};
}

int inv(int a)
{
	const auto res = extgcd(mod, a);
	const int y = res.second;
	return (mod + y % mod) % mod;
}

int fact(int a)
{
	static vector<int> mem(1, 1);
	for(int i = mem.size(); i <= a; ++i) {
		int v = ((int64)i * mem.back()) % mod;
		mem.push_back(v);
	}
	return mem[a];
}

int invfact(int a)
{
	static vector<int> mem(1, 1);
	for(int i = mem.size(); i <= a; ++i) {
		int v = ((int64)inv(i) * mem.back()) % mod;
		mem.push_back(v);
	}
	return mem[a];
}

int nck(int a, int b)
{
	if(a < b)
		return 0;
	int ans = 1;
	ans = ((int64)ans * fact(a)) % mod;
	ans = ((int64)ans * invfact(b)) % mod;
	ans = ((int64)ans * invfact(a - b)) % mod;

	return ans;
}


pair<vector<int>, vector<int> > calculate_table(const int n, const int m, const int k)
{
	vector<int> nt, mt;
	vector<int> cur, next;

	nt.resize(k + 1, -1);
	mt.resize(k + 1, -1);
	cur.resize(k + 1, 0);
	next.resize(k + 1);

	cur[0] = 1;

	for(int gen = 1; gen <= k * 2; ++gen) {

		fill(next.begin(), next.end(), 0);
		next[0] = cur[0];

		for(int i = 1; i <= k; ++i) {
			if(i * 2 > gen)
				continue;
			next[i] = (cur[i] + cur[i - 1]) % mod;
		}

		swap(cur, next);

		if(gen - n >= 0 && gen - n <= 2 * k && (gen - n) % 2 == 0)
			nt[(gen - n) / 2] = cur[(gen - n) / 2];
		if(gen - m >= 0 && gen - m <= 2 * k && (gen - m) % 2 == 0)
			mt[(gen - m) / 2] = cur[(gen - m) / 2];
	}

	for(int i = 0; i <= k; ++i) {

		if(nt[i] == -1) {
			nt[i] = 0;
			for(int j = 0; j <= i; ++j) {
				const int remain = n + i * 2 - k * 2;
				const int diff = i - j;
				nt[i] += ((int64)cur[j] * nck(remain, diff)) % mod;
				nt[i] %= mod;
			}
		}

		if(mt[i] == -1) {
			mt[i] = 0;
			for(int j = 0; j <= i; ++j) {
				const int remain = m + i * 2 - k * 2;
				const int diff = i - j;
				mt[i] += ((int64)cur[j] * nck(remain, diff)) % mod;
				mt[i] %= mod;
			}
		}
	}

	return {nt, mt};
}


int main()
{
	int n, m, k;
	int ans = 0;

	scanf("%d%d%d", &n, &m, &k);

	auto tables = calculate_table(n, m, k);
	const auto &n_table = tables.first;
	const auto &m_table = tables.second;

	for(int nk = 0; nk <= k; ++nk) {

		const int mk = k - nk;

		const int64 x = n_table[nk];
		const int64 y = m_table[mk];
		const int64 xy = (x * y) % mod;
		const int64 combi = nck(n + m + k * 2, n + nk * 2);

		ans += (xy * combi) % mod;
		ans %= mod;
	}

	printf("%d\n", ans);

	return 0;
}