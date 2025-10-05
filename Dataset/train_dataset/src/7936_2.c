#include <bits/stdc++.h>
using namespace std;
const double pi = acos(0.0) * 2.0;
const long double eps = 1e-10;
const int step[8][2] = {{-1, 0}, {0, 1}, {1, 0},  {0, -1},
                        {-1, 1}, {1, 1}, {1, -1}, {-1, -1}};
template <class T>
inline T abs1(T a) {
  return a < 0 ? -a : a;
}
template <typename t, typename t1>
t min1(t a, t1 b) {
  return a < b ? a : b;
}
template <typename t, typename... arg>
t min1(t a, arg... arr) {
  return min1(a, min1(arr...));
}
template <typename t, typename t1>
t max1(t a, t1 b) {
  return a > b ? a : b;
}
template <typename t, typename... arg>
t max1(t a, arg... arr) {
  return max1(a, max1(arr...));
}
inline int jud(double a, double b) {
  if (abs(a) < eps && abs(b) < eps)
    return 0;
  else if (abs1(a - b) / max(abs1(a), abs1(b)) < eps)
    return 0;
  if (a < b) return -1;
  return 1;
}
template <typename t>
inline int jud(t a, t b) {
  if (a < b) return -1;
  if (a == b) return 0;
  return 1;
}
template <typename it, typename t1>
inline int find(t1 val, it a, int na, bool f_small = 1, bool f_lb = 1) {
  if (na == 0) return 0;
  int be = 0, en = na - 1;
  if (*a <= *(a + na - 1)) {
    if (f_lb == 0)
      while (be < en) {
        int mid = (be + en + 1) / 2;
        if (jud(*(a + mid), val) != 1)
          be = mid;
        else
          en = mid - 1;
      }
    else
      while (be < en) {
        int mid = (be + en) / 2;
        if (jud(*(a + mid), val) != -1)
          en = mid;
        else
          be = mid + 1;
      }
    if (f_small && jud(*(a + be), val) == 1) be--;
    if (!f_small && jud(*(a + be), val) == -1) be++;
  } else {
    if (f_lb)
      while (be < en) {
        int mid = (be + en + 1) / 2;
        if (jud(*(a + mid), val) != -1)
          be = mid;
        else
          en = mid - 1;
      }
    else
      while (be < en) {
        int mid = (be + en) / 2;
        if (jud(*(a + mid), val) != 1)
          en = mid;
        else
          be = mid + 1;
      }
    if (!f_small && jud(*(a + be), val) == -1) be--;
    if (f_small && jud(*(a + be), val) == 1) be++;
  }
  return be;
}
template <class T>
inline T lowb(T num) {
  return num & (-num);
}
inline int bitnum(unsigned int nValue) { return __builtin_popcount(nValue); }
inline int bitnum(int nValue) { return __builtin_popcount(nValue); }
inline int bitnum(unsigned long long nValue) {
  return __builtin_popcount(nValue) + __builtin_popcount(nValue >> 32);
}
inline int bitnum(long long nValue) {
  return __builtin_popcount(nValue) + __builtin_popcount(nValue >> 32);
}
inline int bitmaxl(unsigned int a) {
  if (a == 0) return 0;
  return 32 - __builtin_clz(a);
}
inline int bitmaxl(int a) {
  if (a == 0) return 0;
  return 32 - __builtin_clz(a);
}
inline int bitmaxl(unsigned long long a) {
  int temp = a >> 32;
  if (temp) return 32 - __builtin_clz(temp) + 32;
  return bitmaxl(int(a));
}
inline int bitmaxl(long long a) {
  int temp = a >> 32;
  if (temp) return 32 - __builtin_clz(temp) + 32;
  return bitmaxl(int(a));
}
long long pow(long long n, long long m, long long mod = 0) {
  if (m < 0) return 0;
  long long ans = 1;
  long long k = n;
  while (m) {
    if (m & 1) {
      ans *= k;
      if (mod) ans %= mod;
    }
    k *= k;
    if (mod) k %= mod;
    m >>= 1;
  }
  return ans;
}
template <class t1, class t2>
inline void add(t1& a, t2 b, int mod = -1) {
  if (mod == -1) mod = 1000000007;
  a += b;
  while (a >= mod) a -= mod;
  while (a < 0) a += mod;
}
template <class t>
void output1(t arr) {
  for (int i = 0; i < (int)arr.size(); i++) cerr << arr[i] << ' ';
  cerr << endl;
}
template <class t>
void output2(t arr) {
  for (int i = 0; i < (int)arr.size(); i++) output1(arr[i]);
}
const int maxn = 100100;
const int mod = 998244353;
int n;
pair<long long, pair<long long, long long> > orig[maxn];
struct Info {
  pair<long long, long long> time;
  long long p;
  bool operator<(const Info& other) const {
    return time.first * other.time.second < time.second * other.time.first;
  }
  bool operator==(const Info& other) const {
    return time.first * other.time.second == time.second * other.time.first;
  }
  bool operator>(const Info& other) const { return other < *this; }
  bool operator<=(const Info& other) const {
    return *this < other || *this == other;
  }
  bool operator>=(const Info& other) const {
    return other < *this || *this == other;
  }
};
vector<Info> Merge(const vector<Info>& a, const vector<Info>& b) {
  vector<Info> ans;
  ans.reserve(a.size() + b.size());
  int i = 0, j = 0;
  for (; i < (int)a.size() && j < (int)b.size();) {
    if (a[i] == b[j]) {
      ans.push_back({a[i].time, (a[i].p + b[j].p) % mod});
      i++;
      j++;
    } else if (a[i] > b[j]) {
      if (a[i].p) ans.push_back(a[i]);
      i++;
    } else {
      if (b[j].p) ans.push_back(b[j]);
      j++;
    }
  }
  while (i < (int)a.size()) {
    ans.push_back(a[i]);
    i++;
  }
  while (j < (int)b.size()) {
    ans.push_back(b[j]);
    j++;
  }
  return ans;
}
vector<Info> MergeDp(const vector<Info>& a, const vector<Info>& b) {
  vector<Info> ra = a, rb = b;
  for (long long i = 0, j = 0, sum = 0; i < a.size(); i++) {
    while (j < b.size() && b[j] >= a[i]) {
      add(sum, b[j].p, mod);
      j++;
    }
    ra[i].p *= sum;
    ra[i].p %= mod;
  }
  for (long long i = 0, j = 0, sum = 0; j < b.size(); j++) {
    while (i < a.size() && a[i] > b[j]) {
      add(sum, a[i].p, mod);
      i++;
    }
    rb[j].p *= sum;
    rb[j].p %= mod;
  }
  return Merge(ra, rb);
}
vector<Info> all_info[maxn][4];
vector<Info> temp_info[4];
int all_size = 0;
int main() {
  ios_base::sync_with_stdio(0);
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    scanf("%lld%lld%lld", &orig[i].first, &orig[i].second.first,
          &orig[i].second.second);
    orig[i].second.second *= pow(100, mod - 2, mod);
    orig[i].second.second %= mod;
  }
  for (int l = 0; l < n - 1; l++) {
    for (int cate = 0; cate < 4; cate++) {
      int r = l + 1;
      long long p = 1, dv = 0;
      p *= (cate & 1) ? orig[l].second.second : mod + 1 - orig[l].second.second;
      dv += (cate & 1) ? orig[l].second.first : -orig[l].second.first;
      p *= (cate & 2) ? orig[r].second.second : mod + 1 - orig[r].second.second;
      dv += (cate & 2) ? -orig[r].second.first : orig[r].second.first;
      dv = max(0ll, dv);
      p %= mod;
      all_info[l][cate] = {{{orig[r].first - orig[l].first, dv}, p}};
      all_size++;
    }
  }
  for (int i = 0; (1 << i) < (n - 1); i++) {
    for (int j = 0; j * (1 << (i + 1)) < n - 1; j++) {
      int no_a = j * (1 << (i + 1)), no_b = no_a + (1 << i);
      if (no_b >= n - 1) continue;
      for (int f1 = 0; f1 < 2; f1++)
        for (int f2 = 0; f2 < 2; f2++) {
          auto rans1 = MergeDp(all_info[no_a][f1], all_info[no_b][f2 << 1]);
          long long p1 = pow(mod + 1 - orig[no_b].second.second, mod - 2, mod);
          for (auto& it : rans1) {
            it.p *= p1;
            it.p %= mod;
          }
          auto rans2 =
              MergeDp(all_info[no_a][f1 + 2], all_info[no_b][(f2 << 1) + 1]);
          long long p2 = pow(orig[no_b].second.second, mod - 2, mod);
          for (auto& it : rans2) {
            it.p *= p2;
            it.p %= mod;
          }
          temp_info[f1 + (f2 << 1)] = Merge(rans1, rans2);
        }
      for (int i = 0; i < 4; i++) {
        all_info[no_a][i] = temp_info[i];
      }
    }
  }
  long long ans = 0;
  for (int cate = 0; cate < 4; cate++)
    for (const auto it : all_info[0][cate]) {
      if (it.time.second) {
        ans += it.p * it.time.first % mod * pow(it.time.second, mod - 2, mod);
        ans %= mod;
      }
    }
  printf("%lld\n", ans);
  return 0;
}
