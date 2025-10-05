#include <bits/stdc++.h>
using namespace std;
const long long N = 1e5 + 5;
string cad[N];
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.precision(10);
  cout << fixed;
  long long n;
  cin >> n;
  for (long long i = n - 1; i >= 0; i--) {
    cin >> cad[i];
  }
  long long cnt = 0;
  long long ind = -1;
  for (long long i = 0; i < n; i++) {
    for (long long j = 0; j < cad[i].size(); j++) {
      if (cad[i][j] != cad[0][0]) {
        ind = i;
        break;
      }
    }
    if (ind != -1) {
      break;
    }
    cnt = cnt * (cad[i].size() + 1) + cad[i].size();
  }
  if (ind == -1) {
    cout << cnt << endl;
    return 0;
  }
  if (ind == 0) {
    long long sz = cad[0].size();
    long long pos = 0;
    while (pos < sz && cad[0][pos] == cad[0][0]) {
      pos++;
    }
    long long ini = pos;
    pos = sz - 1;
    long long con = 0;
    while (pos >= 0 && cad[0][pos] == cad[0][sz - 1]) {
      pos--;
      con++;
    }
    long long fin = con;
    long long mx = max(ini, fin);
    for (long long i = 0; i < sz; i++) {
      char ss = cad[0][i];
      con = 0;
      while (i < sz && cad[0][i] == ss) {
        i++;
        con++;
      }
      i--;
      mx = max(mx, con);
    }
    if (cad[0][0] == cad[0][sz - 1]) {
      for (long long i = ind + 1; i < n; i++) {
        for (long long j = 0; j < cad[i].size(); j++) {
          if (cad[i][j] == cad[0][0]) {
            mx = max(mx, ini + fin + 1);
          }
        }
      }
    } else {
      for (long long i = ind + 1; i < n; i++) {
        for (long long j = 0; j < cad[i].size(); j++) {
          if (cad[i][j] == cad[0][0]) {
            mx = max(mx, ini + 1);
          } else if (cad[i][j] == cad[0][sz - 1]) {
            mx = max(mx, fin + 1);
          }
        }
      }
    }
    cout << mx << endl;
    return 0;
  }
  long long ini = cnt;
  long long fin = cnt;
  long long mx = cnt;
  for (long long i = 0; i < cad[ind].size(); i++) {
    if (cad[ind][i] == cad[0][0]) {
      long long con = 0;
      while (i < cad[ind].size() && cad[ind][i] == cad[0][0]) {
        i++;
        con++;
      }
      mx = max(mx, cnt * (con + 1) + con);
      if (i == con) {
        ini = cnt * (con + 1) + con;
      }
      if (i == cad[ind].size()) {
        fin = cnt * (con + 1) + con;
      }
      i--;
    }
  }
  for (long long i = ind + 1; i < n; i++) {
    for (long long j = 0; j < cad[i].size(); j++) {
      if (cad[i][j] == cad[0][0]) {
        mx = max(mx, ini + fin + 1);
      }
    }
  }
  cout << mx << endl;
  return 0;
}
