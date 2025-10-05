#include <bits/stdc++.h>
using namespace std;
long long n;
int ans = 0;
int digcnt;
long long pref[20];
long long pwr10[20];
long long count_pref(long long x, int digits) {
  if (digits == 0) return n;
  long long Ans = 0;
  for (int i = digits; i < digcnt; i++) {
    Ans += pwr10[i - digits];
  }
  if (x < pref[digits]) {
    Ans += pwr10[digcnt - digits];
  } else if (x == pref[digits]) {
    Ans += n - x * pwr10[digcnt - digits] + 1;
  }
  return Ans;
}
void dfs(long long x, int digits, int upto, long long presum) {
  if (upto == digcnt) {
    if (x > pref[digits]) return;
    if (x == pref[digits] && digits < upto) {
      long long cursum = presum;
      for (long long nxt = pref[digits] * 10LL; nxt <= pref[digits + 1];
           nxt++) {
        if (digits || nxt) {
          dfs(nxt, digits + 1, upto, cursum + 1);
          cursum += count_pref(nxt, digits + 1);
        }
      }
      return;
    }
  }
  if (digits == upto) {
    ans -= (((presum + 1LL - x) + 1000000LL * 998244353LL) / 998244353LL -
            1000000LL);
    if (ans < 0) ans += 1000000007;
    if (ans >= 1000000007) ans -= 1000000007;
    return;
  }
  if (digits > 0) {
    long long mina = x * pwr10[upto - digits];
    long long maxa = mina + pwr10[upto - digits] - 1;
    long long mini = presum;
    long long maxi = presum + count_pref(x, digits);
    if ((((maxi - mina) + 1000000LL * 998244353LL) / 998244353LL - 1000000LL) ==
        (((mini - maxa) + 1000000LL * 998244353LL) / 998244353LL - 1000000LL)) {
      ans -= (((long long)((((maxi - mina) + 1000000LL * 998244353LL) /
                                998244353LL -
                            1000000LL) +
                           1000000007) *
               (long long)(pwr10[upto - digits] % 1000000007)) %
              1000000007);
      if (ans < 0) ans += 1000000007;
      if (ans >= 1000000007) ans -= 1000000007;
      return;
    }
  }
  long long cursum = presum;
  for (long long nxt = x * 10LL; nxt < (x + 1LL) * 10LL; nxt++) {
    if (digits || nxt) {
      dfs(nxt, digits + 1, upto, cursum + 1);
      cursum += count_pref(nxt, digits + 1);
    }
  }
}
int main() {
  pwr10[0] = 1LL;
  for (int i = 1; i <= 15; i++) {
    pwr10[i] = 10LL * pwr10[i - 1];
  }
  scanf("%lld", &n);
  char tmp[20];
  sprintf(tmp, "%lld", n);
  digcnt = strlen(tmp);
  long long tmp2 = n;
  for (int i = 0; i < digcnt; i++) {
    pref[digcnt - i] = tmp2;
    tmp2 /= 10LL;
  }
  for (int i = 1; i <= digcnt; i++) {
    dfs(0, 0, i, -1);
  }
  ans = (((long long)(ans) * (long long)(998244353)) % 1000000007);
  printf("%d", ans);
  return 0;
}
