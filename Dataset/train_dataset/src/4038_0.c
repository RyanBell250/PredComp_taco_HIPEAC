#include <bits/stdc++.h>
using namespace std;
const int N = 200005;
int dr8[] = {0, 0, 1, -1, 1, 1, -1, -1};
int dc8[] = {1, -1, 0, 0, -1, 1, -1, 1};
int dr4[] = {0, 1, -1, 0};
int dc4[] = {1, 0, 0, -1};
int pts[200010];
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(NULL);
  cout.tie(NULL);
  int n, k;
  cin >> n >> k;
  int l, r;
  int ans = 0;
  int mm = 200005;
  priority_queue<pair<int, int> > pq;
  memset(pts, 0, sizeof pts);
  priority_queue<int> pending;
  vector<vector<pair<int, int> > > all(mm);
  for (int i = 1; i <= n; ++i) {
    cin >> l >> r;
    all[l].push_back({r, i});
    ++pts[l];
    --pts[r + 1];
  }
  int csum = 0;
  for (int i = 1; i <= mm; ++i) {
    csum += pts[i];
    pts[i] = csum;
  }
  vector<int> inds;
  for (int i = 1; i <= mm; ++i) {
    for (auto ss : all[i]) {
      pq.push(ss);
    }
    while (pts[i] - (int)pending.size() > k) {
      ++ans;
      pending.push(-pq.top().first);
      inds.push_back(pq.top().second);
      pq.pop();
    }
    while (!pending.empty() and -pending.top() <= i) {
      pending.pop();
    }
  }
  cout << ans << '\n';
  for (auto ind : inds) {
    cout << ind << " ";
  }
  cout << "\n";
  return 0;
}
