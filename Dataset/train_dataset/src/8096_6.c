#include <bits/stdc++.h>
using namespace std;

int main(){
  int N, M;
  cin>> N >> M;
  vector<int> X(N+1), Y(M+1);
  cin >> X[0] >> Y[0];
  for (int i=1; i<N+1; i++) cin >> X[i];
  for (int i=1; i<M+1; i++) cin >> Y[i];
  sort(X.begin(), X.end());
  sort(Y.begin(), Y.end());
  if (X[N] < Y[0]) cout << "No War" << endl;
  else cout << "War" << endl;
}
