#include <bits/stdc++.h>
using namespace std;
const int inf = 0x3f3f3f3f;
unsigned long long mod = 123456789;
double eps = 1e-9;
using namespace std;
const int maxn = 1e5 + 10;
vector<int> v[maxn];
int a[maxn];
int main() {
  int n, k, m;
  cin >> n >> k >> m;
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
    v[a[i] % m].push_back(a[i]);
  }
  int flag = 0;
  for (int i = 0; i <= m - 1; i++) {
    if (v[i].size() >= k) {
      flag = 1;
      puts("Yes");
      for (int j = 0; j < k; j++) {
        printf("%d ", v[i][j]);
      }
      puts("");
      break;
    }
  }
  if (!flag) {
    puts("No");
  }
}
