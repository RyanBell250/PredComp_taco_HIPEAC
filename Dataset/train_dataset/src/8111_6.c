
#include<iostream>
#include<iomanip>
#include<algorithm>
#include<vector>
#include<stack>
#include<queue>
#include<map>
#include<set>
#include<tuple>
#include<cmath>
#include<random>
#include<cassert>
using namespace std;
using ll = long long;
int n, m;
int x[112345];
int ch[112345];
int lost[112345];
int main() {
  ios::sync_with_stdio(false), cin.tie(0);
  cin >> n >> m;
  vector<int> v;
  int now = n - m;
  for(int i = 0; i < m; i++) cin >> x[i], ch[x[i]] = 1, v.emplace_back(x[i]);
  lost[1] = now;
  for(int i = 2; i <= n; i++) {
    vector<int> nv;
    for(auto e : v) {
      if(e == n || ch[e+1]) {
      } else {
        ch[e+1] = 1;
        now--;
        nv.emplace_back(e + 1);
      }
    }
    v = nv;
    lost[i] = now;
  }
  int q;
  cin >> q;
  vector<int> ans(int(1e5) + 1, -1);
  int head = n;
  for(int i = 0; i <= int(1e5); i++) {
    while(head >= 1 && lost[head] <= i) head--;
    ans[i] = head == n ? -1 : head + 1;
  }
  for(int i = 0; i < q; i++) {
    int x;
    cin >> x;
    cout << ans[x] << "\n";
  }
  return 0;
}
