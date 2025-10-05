#include <bits/stdc++.h>
using namespace std;
long long int mypow(long long int a, long long int b) {
  long long int res = 1;
  while (b) {
    if (b & 1) res = res * a;
    b >>= 1;
    if (b) {
      a = a * a;
    }
  }
  return res;
}
long long int modpow(long long int a, long long int b,
                     long long int m = 1000000007) {
  a %= m;
  long long int res = 1;
  while (b) {
    if (b & 1) res = res * a % m;
    b >>= 1;
    if (b) {
      a = a * a % m;
    }
  }
  return res;
}
long long int modinv(long long int a) {
  return modpow(a, 1000000007 - 2, 1000000007);
}
vector<long long int> power(11);
void computepower() {
  vector<int> p = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31};
  for (int(i) = (0); (i) < (p.size()); ++(i)) {
    power[i] = modpow(2, p[i]) - 1;
  }
}
vector<long long int> powerof2(60);
void computepower2() {
  powerof2[0] = 1;
  for (int(i) = (1); (i) < (60); ++(i)) {
    powerof2[i] = powerof2[i - 1] * 2;
  }
}
vector<long long int> modinvr(100005);
void computemodinvr() {
  modinvr[0] = modinvr[1] = 1;
  for (int i = 2; i < 100005; i++)
    modinvr[i] =
        modinvr[1000000007 % i] * (1000000007 - 1000000007 / i) % 1000000007;
}
vector<long long int> modinvrfact(100005);
vector<long long int> factr(100005);
void computeodinvrfact() {
  factr[0] = 1;
  modinvrfact[0] = 1;
  for (int(i) = (1); (i) < (100005); ++(i)) {
    factr[i] = (factr[i - 1] * i) % 1000000007;
    modinvrfact[i] = modinv(factr[i]) % 1000000007;
  }
}
bool mycompr(pair<int, int> i1, pair<int, int> i2) {
  return i1.second > i2.second;
}
void unique_elem(vector<long long int> &v) {
  sort(v.begin(), v.end());
  auto ip = unique(v.begin(), v.end());
  v.resize(distance(v.begin(), ip));
}
void unique_elem_with_count(vector<long long int> &a,
                            vector<long long int> &unique,
                            vector<long long int> &cnt_unique,
                            vector<long long int> &sum_unique, int n) {
  sort(a.begin(), a.end());
  long long int j = 0;
  long long int sum = 0;
  while (j < n) {
    long long int cnt = 1;
    if (j != n - 1) {
      while (a[j + 1] == a[j]) {
        cnt++;
        j++;
        if (j == n - 1) {
          break;
        }
      }
    }
    sum += cnt;
    unique.push_back(a[j]);
    cnt_unique.push_back(cnt);
    sum_unique.push_back(sum);
    j++;
  }
}
void bfs(int root, int par, vector<bool> &vis, vector<long long int> &dist,
         vector<vector<int> > &adj) {
  queue<int> q;
  q.push(root);
  dist[root] = 0;
  vis[root] = true;
  while (!q.empty()) {
    int p = q.front();
    q.pop();
    for (int i = 0; i < adj[p].size(); i++) {
      if (vis[adj[p][i]] == false) {
        dist[adj[p][i]] = dist[p] + 1;
        q.push(adj[p][i]);
        vis[adj[p][i]] = true;
      }
    }
  }
}
void graph(vector<vector<int> > &adj, int m) {
  int x, y;
  for (int(i) = (0); (i) < (m); ++(i)) {
    cin >> x >> y;
    adj[x].push_back(y);
    adj[y].push_back(x);
  }
}
void decToBinary(int n, vector<int> &binaryNum) {
  binaryNum.resize(32, 0);
  int i = 0;
  while (n > 0) {
    binaryNum[i] = n % 2;
    n = n / 2;
    i++;
  }
}
long long int Binarytodec(string &st) {
  computepower2();
  long long int len = st.size();
  long long int num = 0;
  for (int(i) = (0); (i) < (st.size()); ++(i)) {
    if (st[i] == '1') {
      num += powerof2[len - i - 1];
    }
  }
  return num;
}
vector<int> spf(1000005);
void sieve() {
  spf[1] = 1;
  for (int i = 2; i < 1000005; i++) spf[i] = i;
  for (int i = 4; i < 1000005; i += 2) spf[i] = 2;
  for (int i = 3; i * i < 1000005; i++) {
    if (spf[i] == i) {
      for (int j = i * i; j < 1000005; j += i) {
        if (spf[j] == j) {
          spf[j] = i;
        }
      }
    }
  }
}
vector<int> getFactorization(int x) {
  vector<int> ret;
  map<int, int> fact;
  while (x != 1) {
    ret.push_back(spf[x]);
    if (fact.find(spf[x]) == fact.end()) {
      fact[spf[x]] = 1;
    } else {
      fact[spf[x]]++;
    }
    x = x / spf[x];
  }
  for (auto it = fact.begin(); it != fact.end(); it++) {
    if (it->second & 1) {
      ret.push_back(it->first);
    }
  }
  return ret;
}
bool containsOnlyDigit(string str) {
  int l = str.length();
  for (int i = 0; i < l; i++) {
    if (str.at(i) < '0' || str.at(i) > '9') return false;
  }
  return true;
}
void solve() {
  long long int n, m, x, y;
  cin >> n >> m >> x >> y;
  vector<long long int> a(n);
  long long int cost = 0;
  for (int(i) = (0); (i) < (n); ++(i)) {
    string s;
    cin >> s;
    for (int(i) = (0); (i) < (m); ++(i)) {
      if (s[i] == '.') {
        if (i == m - 1) {
          cost += x;
          continue;
        }
        if (s[i + 1] == '.') {
          cost += min(2 * x, y);
          i++;
        } else {
          cost += x;
        }
      }
    }
  }
  cout << cost << '\n';
}
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int t = 1;
  cin >> t;
  int tt = 1;
  while (t--) {
    solve();
  }
}
