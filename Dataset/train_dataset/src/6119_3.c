#include <bits/stdc++.h>
using namespace std;
vector<pair<int, string> > vet;
int out = 0, s;
string make(string in) {
  string res;
  for (int i = 0; i < s; ++i) {
    if (in[i] == 'X') {
      if (vet[0].second[i] == '0')
        res += '1';
      else
        res += '0';
    } else
      res += in[i];
  }
  return res;
}
bool good(pair<int, string> a, string b) {
  int r = 0;
  for (int i = 0; i < s; ++i)
    if (a.second[i] == b[i]) ++r;
  return r == a.first;
}
bool check(string res) {
  for (int i = 0, t = vet.size(); i < t; ++i) {
    if (!good(vet[i], res)) return false;
  }
  return true;
}
void search(int p, string str, int k) {
  if (p == vet[0].first) {
    string res = make(str);
    if (check(res)) ++out;
  } else {
    for (int i = k; i < s; ++i) {
      string tes = str;
      tes[i] = vet[0].second[i];
      search(p + 1, tes, i + 1);
    }
  }
}
int main() {
  int m, n;
  string in, aux;
  scanf("%d%d ", &m, &n);
  s = m;
  while (n--) {
    cin >> in >> m;
    vet.push_back(make_pair(m, in));
  }
  sort(vet.begin(), vet.end());
  for (int i = 0; i < s; ++i) aux += 'X';
  search(0, aux, 0);
  printf("%d\n", out);
  return 0;
}
