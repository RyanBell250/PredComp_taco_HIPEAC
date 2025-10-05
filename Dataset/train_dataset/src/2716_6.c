#include <bits/stdc++.h>
using namespace std;
int N, M, UsedNum;
long long Y;
vector<int> Adj[20];
bool Known[20];
int Num[20], Given[20];
int InE[20];
long long Opt[70000];
bool HasCircle(int Cur) {
  if (Known[Cur]) return 1;
  Known[Cur] = 1;
  for (typeof(Adj[Cur].begin()) it = Adj[Cur].begin(); it != Adj[Cur].end();
       ++it)
    if (HasCircle(*it)) return 1;
  Known[Cur] = 0;
  return 0;
}
bool Checked() {
  fill(Known, Known + N, 0);
  for (int i = 0; i < N; ++i)
    if (HasCircle(i)) return 0;
  return 1;
}
long long Find() {
  fill(Opt, Opt + (1 << N), 0);
  Opt[0] = 1;
  for (int i = 0; i < (1 << N) - 1; ++i)
    if (Opt[i] > 0) {
      int c = __builtin_popcount(i);
      if (Given[c] == -1) {
        for (int j = 0; j < N; ++j)
          if (Num[j] == -1 && (i & (1 << j)) == 0 && (i & InE[j]) == InE[j])
            Opt[i ^ (1 << j)] += Opt[i];
      } else {
        if ((i & InE[Given[c]]) == InE[Given[c]])
          Opt[i ^ (1 << Given[c])] += Opt[i];
      }
    }
  return Opt[(1 << N) - 1];
}
void GetAns() {
  fill(Num, Num + N, -1);
  fill(Given, Given + N, -1);
  UsedNum = 0;
  for (int i = 0; i < N; ++i) {
    bool Flag = 0;
    for (int j = 0; j < N; ++j)
      if ((UsedNum & (1 << j)) == 0) {
        Num[i] = j;
        Given[j] = i;
        UsedNum ^= (1 << j);
        long long Cnt = Find();
        if (Cnt >= Y) {
          Flag = 1;
          break;
        }
        Y -= Cnt;
        Num[i] = -1;
        Given[j] = -1;
        UsedNum ^= (1 << j);
      }
    if (!Flag) {
      puts("The times have changed");
      return;
    }
  }
  for (int i = 0; i < N; ++i)
    printf("%d%c", Num[i] + 1, (i == N - 1) ? '\n' : ' ');
}
int main() {
  cin >> N >> Y >> M;
  Y -= 2000LL;
  fill(InE, InE + N, 0);
  for (int i = 0; i < M; ++i) {
    int U, V;
    cin >> U >> V;
    --U, --V;
    Adj[U].push_back(V);
    InE[V] |= (1 << U);
  }
  if (!Checked())
    puts("The times have changed");
  else
    GetAns();
}
