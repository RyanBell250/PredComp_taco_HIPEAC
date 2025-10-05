#include <bits/stdc++.h>
const int maxn = 1e5 + 5;
using namespace std;
long long mask[8], inp[3];
vector<int> mp[maxn];
int main(void) {
  int a[1005], b[1005], c[1005];
  int t;
  scanf("%d", &t);
  for (int i = 1; i < maxn; i++)
    for (int j = i; j < maxn; j += i) mp[j].push_back(i);
  while (t--) {
    vector<int> mp1, mp2, mp3, npt, np;
    memset(mask, 0, sizeof(mask));
    scanf("%lld%lld%lld", &inp[0], &inp[1], &inp[2]);
    mp1 = mp[inp[0]], mp2 = mp[inp[1]], mp3 = mp[inp[2]];
    np.insert(np.end(), mp1.begin(), mp1.end());
    np.insert(np.end(), mp2.begin(), mp2.end());
    np.insert(np.end(), mp3.begin(), mp3.end());
    sort(np.begin(), np.end());
    np.erase(unique(np.begin(), np.end()), np.end());
    vector<int>::iterator t;
    for (t = np.begin(); t != np.end(); t++) {
      int f = 0;
      if (inp[0] % (*t) == 0) f += 1;
      if (inp[1] % (*t) == 0) f += 2;
      if (inp[2] % (*t) == 0) f += 4;
      mask[f]++;
    }
    long long cnt = 0;
    for (int i = 1; i <= 7; i++) {
      for (int j = i; j <= 7; j++) {
        for (int k = j; k <= 7; k++) {
          if ((i | j | k) != 7)
            ;
          else if ((i == j || j == k) && (j == 1 || j == 2 || j == 4))
            ;
          else if (i == j && j == k)
            cnt += mask[i] * (mask[i] + 1) * (mask[i] + 2) / 6;
          else if (i == j)
            cnt += mask[i] * (mask[i] + 1) * mask[k] / 2;
          else if (j == k)
            cnt += mask[j] * (mask[j] + 1) * mask[i] / 2;
          else {
            cnt += mask[i] * mask[j] * mask[k];
          }
        }
      }
    }
    printf("%lld\n", cnt);
  }
  return 0;
}
