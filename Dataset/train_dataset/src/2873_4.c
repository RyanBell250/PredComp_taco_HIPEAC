#include <bits/stdc++.h>
using namespace std;
template <class C>
constexpr int sz(const C &c) {
  return int(c.size());
}
using ll = long long;
constexpr const char nl = '\n', sp = ' ';
template <class T, class IndexType>
struct OfflineSemiSparseFenwickTree2D {
  static_assert(is_integral<IndexType>::value, "IndexType must be integeral");
  int N;
  vector<int> st, cnt;
  vector<IndexType> inds;
  vector<T> BIT;
  int getInd(int i, IndexType j) {
    return upper_bound(inds.begin() + st[i], inds.begin() + st[i] + cnt[i], j) -
           inds.begin() - st[i];
  }
  OfflineSemiSparseFenwickTree2D(int N, vector<pair<int, IndexType>> updateInds)
      : N(N), st(N + 1, 0), cnt(N + 1, 0) {
    sort(updateInds.begin(), updateInds.end(),
         [&](const pair<int, IndexType> &a, const pair<int, IndexType> &b) {
           return a.second < b.second;
         });
    vector<IndexType> last(N + 1, IndexType());
    for (auto &&u : updateInds)
      for (int i = u.first + 1; i <= N; i += i & -i)
        if (cnt[i] == 0 || u.second != last[i]) {
          cnt[i]++;
          last[i] = u.second;
        }
    for (int i = 1; i <= N; i++) st[i] = st[i - 1] + cnt[i - 1];
    inds.resize(st[N] + cnt[N]);
    BIT.resize(st[N] + cnt[N]);
    fill(cnt.begin(), cnt.end(), 0);
    for (auto &&u : updateInds)
      for (int i = u.first + 1; i <= N; i += i & -i)
        if (cnt[i] == 0 || u.second != inds[st[i] + cnt[i] - 1])
          inds[st[i] + cnt[i]++] = u.second;
  }
  void update(int i, IndexType j, T v) {
    for (i++; i <= N; i += i & -i)
      for (int s = st[i], c = cnt[i], y = getInd(i, j); y <= c; y += y & -y)
        BIT[s + y - 1] += v;
  }
  T query(int d, IndexType r) {
    T ret = T();
    for (d++; d > 0; d -= d & -d)
      for (int s = st[d], y = getInd(d, r); y > 0; y -= y & -y)
        ret += BIT[s + y - 1];
    return ret;
  }
  T query(int d, IndexType l, IndexType r) {
    return query(d, r) - query(d, l - 1);
  }
  T query(int u, int d, IndexType l, IndexType r) {
    return query(d, l, r) - query(u - 1, l, r);
  }
};
template <class T>
T mulMod(T a, T b, T mod) {
  return a * b % mod;
}
template <class T, class U>
T powMod(T base, U pow, T mod) {
  T x = 1;
  for (; pow > 0; pow >>= 1, base = mulMod(base, base, mod))
    if (pow & 1) x = mulMod(x, base, mod);
  return x;
}
template <class T>
T mulInvModPrime(T a, T p) {
  return powMod(a, p - 2, p);
}
template <class T>
T divModPrime(T a, T b, T p) {
  return mulMod(a, mulInvModPrime(b, p), p);
}
const int MAXA = 2e5 + 5;
const ll MOD = 1e9 + 7;
struct Val {
  int v;
  Val(int v = 1) : v(v) {}
  Val &operator+=(const Val &o) {
    v = mulMod(ll(v), ll(o.v), MOD);
    return *this;
  }
  Val operator-(const Val &o) const {
    return Val(divModPrime(ll(v), ll(o.v), MOD));
  }
};
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int N;
  cin >> N;
  vector<int> SPF(MAXA + 1);
  iota(SPF.begin(), SPF.end(), 0);
  SPF[0] = SPF[1] = -1;
  vector<int> primes;
  for (int i = 2; i <= MAXA; i++) {
    if (SPF[i] == i) primes.push_back(i);
    for (int j = 0;
         j < sz(primes) && i * primes[j] <= MAXA && primes[j] <= SPF[i]; j++)
      SPF[i * primes[j]] = primes[j];
  }
  vector<int> last(MAXA + 1, -1);
  vector<pair<int, int>> updateInds;
  vector<int> updateVals;
  for (int i = 0; i < N; i++) {
    int a;
    cin >> a;
    while (a != 1) {
      int p = SPF[a], invP = mulInvModPrime(ll(p), MOD), cur = 1;
      for (; a % p == 0; a /= p) {
        cur *= p;
        updateInds.emplace_back(i, last[cur]);
        updateInds.emplace_back(i, i);
        updateVals.push_back(invP);
        updateVals.push_back(p);
        last[cur] = i;
      }
    }
  }
  OfflineSemiSparseFenwickTree2D<Val, int> ft(N, updateInds);
  for (int i = 0; i < sz(updateVals); i++)
    ft.update(updateInds[i].first, updateInds[i].second, updateVals[i]);
  int Q;
  cin >> Q;
  ll ans = 0;
  for (int i = 0; i < Q; i++) {
    int x, y;
    cin >> x >> y;
    int l = (ans + x) % N;
    int r = (ans + y) % N;
    if (l > r) swap(l, r);
    cout << (ans = ft.query(r, l, N - 1).v) << nl;
  }
  return 0;
}
