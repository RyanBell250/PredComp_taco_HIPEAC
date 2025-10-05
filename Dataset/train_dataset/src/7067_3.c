#include <bits/stdc++.h>
using namespace std;
const int N = 5000;
const int M = 1000000;
int n, k, a[N], cnt[N], used[N];
int qt[M + 3], pt[M + 3];
pair<int, int> *v[M + 3];
int r[N * N], cr;
int main() {
  scanf("%d%d", &n, &k);
  for (int i = (0); i <= ((n)-1); i++) scanf("%d", &a[i]);
  sort(a, a + n);
  for (int i = (0); i <= ((n)-1); i++)
    for (int j = (0); j <= ((i)-1); j++) qt[a[i] - a[j]]++;
  for (int i = (0); i <= ((M + 3) - 1); i++)
    if (qt[i]) {
      qt[i] = min(qt[i], 9);
      v[i] = new pair<int, int>[qt[i]];
    }
  for (int i = (0); i <= ((n)-1); i++)
    for (int j = (0); j <= ((i)-1); j++)
      if (pt[a[i] - a[j]] < 9)
        v[a[i] - a[j]][pt[a[i] - a[j]]++] = make_pair(i, j);
  for (int d = 1; d <= M + 1; d++) {
    vector<int> us;
    for (int t = (0); t <= ((k + 1) - 1); t++) {
      cr = 0;
      bool ok = true;
      for (int i = d; i <= M; i += d) {
        if (qt[i] == 9) {
          ok = false;
          break;
        }
        for (int j = 0; j < qt[i]; j++) {
          if (used[v[i][j].first]) continue;
          if (used[v[i][j].second]) continue;
          cnt[v[i][j].first]++;
          cnt[v[i][j].second]++;
          r[cr++] = v[i][j].first;
          r[cr++] = v[i][j].second;
        }
      }
      if (!ok) break;
      if (!cr) {
        cout << d << endl;
        return 0;
      }
      int mx = 0, mv = -1;
      for (int i = (0); i <= ((cr)-1); i++) {
        if (mx < cnt[r[i]]) {
          mx = cnt[r[i]];
          mv = r[i];
        }
        cnt[r[i]] = 0;
      }
      used[mv] = true;
      us.push_back(mv);
    }
    for (int i = (0); i <= (((int)((us).end() - (us).begin())) - 1); i++)
      used[us[i]] = false;
  }
  return 0;
}
