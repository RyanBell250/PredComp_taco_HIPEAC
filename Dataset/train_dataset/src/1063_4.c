#include <bits/stdc++.h>
using namespace std;
void _print(long long int t) { cerr << t; }
void _print(int t) { cerr << t; }
void _print(string t) { cerr << t; }
void _print(char t) { cerr << t; }
void _print(long double t) { cerr << t; }
void _print(double t) { cerr << t; }
void google(int t) { cout << "Case #" << t << ": "; }
template <class T, class V>
void _print(pair<T, V> p);
template <class T>
void _print(vector<T> v);
template <class T>
void _print(set<T> v);
template <class T, class V>
void _print(map<T, V> v);
template <class T>
void _print(multiset<T> v);
template <class T, class V>
void _print(pair<T, V> p) {
  cerr << "{";
  _print(p.ff);
  cerr << ",";
  _print(p.ss);
  cerr << "}";
}
template <class T>
void _print(vector<T> v) {
  cerr << "[ ";
  for (T i : v) {
    _print(i);
    cerr << " ";
  }
  cerr << "]";
}
template <class T>
void _print(set<T> v) {
  cerr << "[ ";
  for (T i : v) {
    _print(i);
    cerr << " ";
  }
  cerr << "]";
}
template <class T>
void _print(multiset<T> v) {
  cerr << "[ ";
  for (T i : v) {
    _print(i);
    cerr << " ";
  }
  cerr << "]";
}
template <class T, class V>
void _print(map<T, V> v) {
  cerr << "[ ";
  for (auto i : v) {
    _print(i);
    cerr << " ";
  }
  cerr << "]";
}
const int Max = 200005;
vector<long long int> edges[Max];
vector<long long int> child(Max, 0);
vector<long long int> depth(Max, 0);
vector<long long int> vis(Max, 0);
int ans = 0;
void dfs1(long long int x, long long int p) {
  for (int i = 0; i < edges[x].size(); i++) {
    long long int new_node = edges[x][i];
    if (new_node != p) {
      depth[new_node] = depth[x] + 1;
      dfs1(new_node, x);
      child[x] += child[new_node] + 1;
    }
  }
}
void dfs2(long long int x, long long int p, long long int temp) {
  if (vis[x] == 1) {
    ans += (temp);
  }
  for (int i = 0; i < edges[x].size(); i++) {
    long long int new_node = edges[x][i];
    if (new_node != p) {
      if (vis[x] == 1) {
        dfs2(new_node, x, temp);
      } else {
        dfs2(new_node, x, temp + 1);
      }
    }
  }
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  long long int i, j, k, n, m, t;
  cin >> n >> k;
  for (i = 0; i < n - 1; i++) {
    int x, y;
    cin >> x >> y;
    edges[x].push_back(y);
    edges[y].push_back(x);
  }
  dfs1(1, 1);
  vector<long long int> contrib(n);
  for (i = 1; i <= n; i++) {
    contrib[i - 1] = depth[i] - child[i];
  }
  sort(contrib.begin(), contrib.end());
  reverse(contrib.begin(), contrib.end());
  long long int ans = 0;
  for (i = 0; i < k; i++) {
    ans += contrib[i];
  }
  cout << ans << endl;
  return 0;
}
