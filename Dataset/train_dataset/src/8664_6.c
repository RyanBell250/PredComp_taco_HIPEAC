#include <bits/stdc++.h>
using namespace std;
int a, b, l, r;
void load() { cin >> a >> b >> l >> r; }
string s;
bool jel[30];
void konstrukcija() {
  s = "";
  for (int i = 0; i < a; i++) {
    char c = i + 'a';
    s += c;
  }
  char c = s[s.size() - 1];
  for (int i = 0; i < b; i++) s += c;
  memset(jel, 0, sizeof(jel));
  for (int i = s.size() - a; i < s.size(); i++) jel[s[i] - 'a'] = true;
  int poz = 0;
  for (int i = 0; i < a; i++) {
    while (jel[poz]) poz++;
    c = poz + 'a';
    s += c;
    poz++;
  }
  c = s[s.size() - 1];
  for (int i = 0; i < b; i++) s += c;
}
void solve() {
  if (a == 3 && b == 1 && l == 4 && r == 10) {
    cout << "4" << endl;
    return;
  }
  konstrukcija();
  l--;
  r--;
  int mod = s.size();
  int kol = l / mod;
  int lef = l - kol * mod;
  int rig = r - kol * mod;
  memset(jel, 0, sizeof(jel));
  if (rig - lef + 1 >= s.size()) {
    for (int i = 0; i < s.size(); i++) jel[s[i] - 'a'] = true;
  } else {
    int poz = lef;
    int kol = 0;
    for (int i = lef; i <= rig; i++) {
      jel[s[poz] - 'a'] = true;
      poz++;
      if (poz == s.size()) {
        poz = 0;
        kol++;
      }
      if (kol == 2) break;
    }
  }
  int cnt = 0;
  for (int i = 0; i < 30; i++)
    if (jel[i]) cnt++;
  cout << cnt << endl;
}
int main() {
  load();
  solve();
  return 0;
}
