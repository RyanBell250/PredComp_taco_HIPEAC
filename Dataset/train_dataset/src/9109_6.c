#include <bits/stdc++.h>
using namespace std;
inline long long mod(long long n, long long m) {
  long long ret = n % m;
  if (ret < 0) ret += m;
  return ret;
}
long long gcd(long long a, long long b) {
  return (b == 0LL ? a : gcd(b, a % b));
}
long long exp(long long a, long long b, long long m) {
  if (b == 0LL) return 1LL;
  if (b == 1LL) return mod(a, m);
  long long k = mod(exp(a, b / 2, m), m);
  if (b & 1LL) {
    return mod(a * mod(k * k, m), m);
  } else
    return mod(k * k, m);
}
const long long N = 200100;
long long n;
long long a[N];
vector<pair<long long, long long> > factorize(long long X) {
  vector<pair<long long, long long> > ans;
  for (long long i = 2; i <= min((long long)1e6, X); i++) {
    if (X % i == 0) {
      long long k = 0;
      while (X % i == 0) {
        k++;
        X /= i;
      }
      ans.push_back(pair<long long, long long>(i, k));
    }
  }
  if (X > 1) {
    long long sq = sqrtl(X);
    for (long long i = sq - 1; i <= sq + 1; i++) {
      if (i * i == X) {
        ans.push_back(pair<long long, long long>(i, 2));
        X = 1;
        break;
      }
    }
    for (long long i = 1; i <= n; i++) {
      long long g = gcd(a[i], X);
      if (g != 1 and g != X) {
        ans.push_back(pair<long long, long long>(g, 1));
        ans.push_back(pair<long long, long long>(X / g, 1));
        X = 1;
        break;
      }
    }
    if (X > 1) ans.push_back(pair<long long, long long>(X, 1));
  }
  return ans;
}
const long long MX = (1 << 16);
long long mask[(1 << 16) + 100];
void SOS_dp() {
  for (long long i = 0; i < 16; i++) {
    for (long long msk = 0; msk < MX; msk++) {
      if (msk & (1 << i)) mask[msk] += mask[msk ^ (1 << i)];
    }
  }
}
void redo(vector<pair<long long, long long> >& x,
          vector<pair<long long, long long> >& y) {
  vector<pair<long long, long long> > x1, abacaba;
  for (long long i = 0; i < (long long)x.size(); i++) {
    if (x[i].second < y[i].second) {
      x1.push_back(x[i]);
      abacaba.push_back(y[i]);
    }
  }
  x = x1, y = abacaba;
}
int32_t main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  ;
  long long X, Y;
  cin >> n >> X >> Y;
  for (long long i = 1; i <= n; i++) {
    cin >> a[i];
    ;
  }
  if (Y % X != 0) {
    cout << 0 << "\n";
    return 0;
  }
  vector<pair<long long, long long> > x = factorize(X), y = factorize(Y);
  sort(x.begin(), x.end());
  sort(y.begin(), y.end());
  for (auto it : y) {
    long long has = 0;
    for (auto it2 : x) {
      if (it2.first == it.first) has = 1;
    }
    if (!has) x.push_back(pair<long long, long long>(it.first, 0));
  }
  sort(x.begin(), x.end());
  sort(y.begin(), y.end());
  assert((long long)x.size() == (long long)y.size());
  redo(x, y);
  for (long long i = 1; i <= n; i++) {
    long long mini = 0;
    long long val = a[i];
    if (a[i] % X) continue;
    long long id = 0;
    for (auto it : x) {
      long long k = 0;
      while (val % it.first == 0) {
        k++;
        val /= it.first;
      }
      if (k > it.second) mini |= (1 << id);
      id++;
    }
    mask[mini]++;
  }
  SOS_dp();
  long long ans = 0;
  for (long long i = 1; i <= n; i++) {
    long long maxi = 0;
    long long val = a[i];
    if (Y % a[i]) continue;
    long long id = 0;
    for (auto it : y) {
      long long k = 0;
      while (val % it.first == 0) {
        k++;
        val /= it.first;
      }
      if (k < it.second) maxi |= (1 << id);
      id++;
    }
    ans += mask[(MX - 1) ^ (maxi)];
  }
  cout << ans << "\n";
}
