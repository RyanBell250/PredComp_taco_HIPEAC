#include <bits/stdc++.h>
using namespace std;
const long long int inf = 9e18;
const long double pi = 2 * acos(0.0);
const int N = 1000005;
long long int tes, n;
string s;
vector<long long int> sieve(N, 0);
void si() {
  sieve[1] = 1;
  for (int i = 2; i < N; i++) {
    if (sieve[i] == 0) {
      for (int j = i; j < N; j += i) {
        sieve[j] = i;
      }
    }
  }
}
long long int power(long long int x, long long int y) {
  long long int res = 1ll;
  while (y > 0) {
    if (y & 1) res = res * x;
    y >>= 1;
    x = x * x;
  }
  return res;
}
void solve() {
  cin >> s;
  n = (int)((s).size());
  vector<long long int> arr, brr;
  ;
  for (int i = 0; i < n; i++) {
    if (s[i] == 'W' || s[i] == 'S') {
      if (s[i] == 'W')
        arr.push_back(+1);
      else
        arr.push_back(-1);
    } else {
      if (s[i] == 'A')
        brr.push_back(-1);
      else
        brr.push_back(+1);
    }
  }
  vector<long long int> cum_a((int)((arr).size()) + 1, 0),
      cum_b((int)((brr).size()) + 1, 0);
  ;
  for (int i = 0; i < (int)((arr).size()); i++) {
    cum_a[i + 1] = cum_a[i] + arr[i];
  };
  for (int i = 0; i < (int)((brr).size()); i++) {
    cum_b[i + 1] = cum_b[i] + brr[i];
  }
  long long int maxi_a = -inf, mini_a = inf, maxi_b = -inf, mini_b = inf,
                ind_maxi_a = -1, ind_mini_a = -1, ind_maxi_b = -1,
                ind_mini_b = -1;
  ;
  for (int i = 0; i < (int)((arr).size()) + 1; i++) {
    if (cum_a[i] > maxi_a) {
      maxi_a = cum_a[i];
      ind_maxi_a = i;
    } else if (cum_a[i] == maxi_a) {
      ind_maxi_a = i;
    }
    if (cum_a[i] < mini_a) {
      mini_a = cum_a[i];
      ind_mini_a = i;
    }
  };
  for (int i = 0; i < (int)((brr).size()) + 1; i++) {
    if (cum_b[i] > maxi_b) {
      maxi_b = cum_b[i];
      ind_maxi_b = i;
    } else if (cum_b[i] == maxi_b) {
      ind_maxi_b = i;
    }
    if (cum_b[i] < mini_b) {
      mini_b = cum_b[i];
      ind_mini_b = i;
    }
  }
  long long int area = (maxi_a - mini_a + 1) * (maxi_b - mini_b + 1);
  if (ind_maxi_a < ind_mini_a) {
    area = min(area, (max(2ll, maxi_a - mini_a)) * (maxi_b - mini_b + 1));
  }
  if (ind_maxi_b < ind_mini_b) {
    area = min(area, (maxi_a - mini_a + 1) * (max(2ll, maxi_b - mini_b)));
  }
  maxi_a = -inf, mini_a = inf, maxi_b = -inf, mini_b = inf, ind_maxi_a = -1,
  ind_mini_a = -1, ind_maxi_b = -1, ind_mini_b = -1;
  ;
  for (int i = 0; i < (int)((arr).size()) + 1; i++) cum_a[i] *= -1;
  ;
  for (int i = 0; i < (int)((brr).size()) + 1; i++) cum_b[i] *= -1;
  ;
  for (int i = 0; i < (int)((arr).size()) + 1; i++) {
    if (cum_a[i] > maxi_a) {
      maxi_a = cum_a[i];
      ind_maxi_a = i;
    } else if (cum_a[i] == maxi_a) {
      ind_maxi_a = i;
    }
    if (cum_a[i] < mini_a) {
      mini_a = cum_a[i];
      ind_mini_a = i;
    }
  };
  for (int i = 0; i < (int)((brr).size()) + 1; i++) {
    if (cum_b[i] > maxi_b) {
      maxi_b = cum_b[i];
      ind_maxi_b = i;
    } else if (cum_b[i] == maxi_b) {
      ind_maxi_b = i;
    }
    if (cum_b[i] < mini_b) {
      mini_b = cum_b[i];
      ind_mini_b = i;
    }
  }
  if (ind_maxi_a < ind_mini_a) {
    area = min(area, (max(2ll, maxi_a - mini_a)) * (maxi_b - mini_b + 1));
  }
  if (ind_maxi_b < ind_mini_b) {
    area = min(area, (maxi_a - mini_a + 1) * (max(2ll, maxi_b - mini_b)));
  }
  cout << area << "\n";
}
int32_t main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  ;
  cin >> tes;
  while (tes--) {
    solve();
  }
}
