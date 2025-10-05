#include <bits/stdc++.h>
using namespace std;
int last, first;
int level = 0;
int x = 0, y = 0;
void move(string s) {
  if (s == "up") {
    level++;
    y++;
    if (level == last) cout << x << " " << y << endl;
  }
  if (s == "down") {
    level++;
    y--;
    if (level == last) cout << x << " " << y << endl;
  }
  if (s == "right") {
    level++;
    x++;
    if (level == last) cout << x << " " << y << endl;
  }
  if (s == "left") {
    level++;
    x--;
    if (level == last) cout << x << " " << y << endl;
  }
}
void Move1(int n);
void Move2(int n);
void Move3(int n);
void Move4(int n);
void Move1(int n) {
  if (n <= 0) return;
  Move2(n - 1);
  move("up");
  Move1(n - 1);
  move("right");
  Move1(n - 1);
  move("down");
  Move3(n - 1);
}
void Move2(int n) {
  if (n <= 0) return;
  Move1(n - 1);
  move("right");
  Move2(n - 1);
  move("up");
  Move2(n - 1);
  move("left");
  Move4(n - 1);
}
void Move3(int n) {
  if (n <= 0) return;
  Move4(n - 1);
  move("left");
  Move3(n - 1);
  move("down");
  Move3(n - 1);
  move("right");
  Move1(n - 1);
}
void Move4(int n) {
  if (n <= 0) return;
  Move3(n - 1);
  move("down");
  Move4(n - 1);
  move("left");
  Move4(n - 1);
  move("up");
  Move2(n - 1);
}
int main() {
  cin >> first >> last;
  if (last <= 0)
    cout << "0 0" << endl;
  else
    Move1(first);
  return 0;
}
