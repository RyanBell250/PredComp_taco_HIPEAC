#include <bits/stdc++.h>
using namespace std;
int a[10], N, need[10], used[10];
set<string> answer;
char cur[15];
void scan() {
  cin >> N;
  for (int i = 0; i < N; ++i) {
    cin >> a[i];
    need[a[i]] = 1;
  }
}
string toIp(string &str, int t1, int t2, int t3) {
  string res;
  for (int i = 0; i < str.size(); ++i) {
    if (i == t1 || i == t2 || i == t3) res += ".";
    res += str[i];
  }
  return res;
}
int valid(string &str) {
  int x = 0;
  if (str[0] == '0' && str[1] >= '0' && str[1] <= '9') return 0;
  for (int i = 0; i < (int)str.size() - 2; ++i)
    if (str[i] == '.' && str[i + 1] == '0' && str[i + 2] >= '0' &&
        str[i + 2] <= '9')
      return 0;
  for (int i = 0; i < str.size(); ++i) {
    if (str[i] == '.') {
      if (x > 255) return 0;
      x = 0;
    } else
      x = x * 10 + str[i] - '0';
  }
  return x < 256;
}
void check(string str) {
  for (int i = 0; i < 10; ++i)
    if (need[i] && !used[i]) return;
  for (int i = 1; i < str.size(); ++i)
    for (int j = i + 1; j < str.size(); ++j)
      for (int k = j + 1; k < str.size(); ++k) {
        string ip = toIp(str, i, j, k);
        if (valid(ip)) answer.insert(ip);
      }
}
void check(int sz) {
  string t;
  for (int i = 0; i < sz; ++i) t += cur[i];
  string x = t;
  for (int i = t.size() - 1; i >= 0; --i) x = x + t[i];
  check(x);
  x = t;
  for (int i = (int)t.size() - 2; i >= 0; --i) x = x + t[i];
  check(x);
}
void go(int idx, int sz) {
  if (idx == sz) {
    check(sz);
    return;
  }
  for (int i = 0; i < N; ++i) {
    ++used[a[i]];
    cur[idx] = a[i] + '0';
    go(idx + 1, sz);
    --used[a[i]];
  }
}
void solve() {
  if (N < 7)
    for (int i = 2; i <= 6; ++i) go(0, i);
  cout << answer.size() << endl;
  for (set<string>::iterator it = answer.begin(); it != answer.end(); ++it)
    cout << *it << endl;
}
int main() {
  scan();
  solve();
}
