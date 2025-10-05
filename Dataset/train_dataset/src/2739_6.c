#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const ll INF = 1LL << 60;
int N, M;
ll dis[1010][1010];

int main() {
  cin.tie(0);
  ios_base::sync_with_stdio(false);
  cout << fixed << setprecision(10);
  
  cin >> N >> M;
  fill((ll*)dis, (ll*)(dis + 1010), INF);
  for (int i = 0; i < N; i++) dis[i][i] = 0;
  for (int i = 0; i < M; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    a--, b--;
    dis[a][b] = -c;
  }
  for (int k = 0; k < N; k++) for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) {
    dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
  }
  for (int i = 0; i < N; i++) {
    if (dis[i][i] < 0 && dis[0][i] < 1000000000000000LL && dis[i][N - 1] < 1000000000000000LL) {
      cout << "inf" << endl;
      return 0;
    }
  }
  cout << -dis[0][N - 1] << endl;

  return 0;
}