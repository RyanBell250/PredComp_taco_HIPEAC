#include <bits/stdc++.h>
using namespace std;
const int maxn = 5e5;
const int big = 1e9;
long long f[maxn];
int a[maxn], t, tin[maxn], tout[maxn], b[maxn];
vector<int> ed[maxn];
int n;
int random(int x) {
  if (x == 0) return 0;
  return 1ll * rand() * rand() % x;
}
struct line {
  int k;
  long long b;
};
struct node {
  node *ls, *rs;
  int key, priority;
  long long b;
  line nxt;
  node(line new_key) {
    key = new_key.k;
    priority = random(2 * big);
    b = new_key.b;
    nxt = new_key;
    ls = rs = nullptr;
  }
};
node *roots[maxn * 2];
line get(node *v) { return v->nxt; }
void update(node *root) {
  if (root == nullptr) return;
  root->nxt = (line){root->key, root->b};
  if (root->ls == nullptr && root->rs == nullptr)
    return;
  else if (root->ls != nullptr)
    root->nxt = get(root->ls);
}
long double pr(line x1, line x2) { return (x2.b - x1.b) / (1.0 * x1.k - x2.k); }
bool chck(line x1, line x2, line x3) {
  long double y1 = pr(x1, x2);
  long double y2 = pr(x1, x3);
  return (y2 >= y1);
}
long long ff(int x, line y) { return y.b + 1ll * y.k * x; }
void split(node *root, node *&left, node *&right, int x) {
  if (root == nullptr) {
    left = nullptr;
    right = nullptr;
    return;
  }
  if (root->key < x) {
    split(root->rs, root->rs, right, x);
    left = root;
  } else {
    split(root->ls, left, root->ls, x);
    right = root;
  }
  update(root);
}
void merge_tr(node *&root, node *left, node *right) {
  if (left == nullptr || right == nullptr) {
    if (right == nullptr)
      root = left;
    else
      root = right;
    update(root);
    return;
  }
  if (left->priority > right->priority) {
    merge_tr(left->rs, left->rs, right);
    root = left;
  } else {
    merge_tr(right->ls, left, right->ls);
    root = right;
  }
  update(root);
}
void insert_key(node *&root, node *v) {
  if (root == nullptr) {
    root = v;
    update(root);
    return;
  }
  if (root->priority > v->priority) {
    if (root->key > v->key)
      insert_key(root->ls, v);
    else
      insert_key(root->rs, v);
    update(root);
    return;
  }
  split(root, v->ls, v->rs, v->key);
  root = v;
  update(root);
}
bool fndx(node *&x, line y) {
  if (x == nullptr) return false;
  if (x->key == y.k) {
    x->b = min(y.b, x->b);
    update(x);
    return true;
  }
  bool res = 0;
  if (y.k < x->key)
    res = fndx(x->ls, y);
  else
    res = fndx(x->rs, y);
  update(x);
  return res;
}
line less_or_equal(node *root, int k) {
  if (root->key <= k) {
    line x1, x2;
    x1.k = root->key;
    x1.b = root->b;
    if (root->rs != nullptr) {
      x2 = less_or_equal(root->rs, k);
      if (x2.k != -big) x1 = x2;
    }
    return x1;
  } else {
    line x1 = (line){-big, -big};
    if (root->ls != nullptr) x1 = less_or_equal(root->ls, k);
    return x1;
  }
}
line bigger(node *root, int k) {
  if (root->key > k) {
    line x1, x2;
    x1.k = root->key;
    x1.b = root->b;
    if (root->ls != nullptr) {
      x2 = bigger(root->ls, k);
      if (x2.k != -big) x1 = x2;
    }
    return x1;
  } else {
    line x1 = (line){-big, -big};
    if (root->rs != nullptr) x1 = bigger(root->rs, k);
    return x1;
  }
}
void add(int x, int l, int r, int y, line k) {
  node *vertex = new node(k);
  if (roots[x] == nullptr)
    roots[x] = vertex;
  else {
    if (!fndx(roots[x], k)) insert_key(roots[x], vertex);
    line x3 = bigger(roots[x], k.k);
    line x2 = less_or_equal(roots[x], k.k);
    line x1 = less_or_equal(roots[x], x2.k - 1);
    if (x3.k != -big && x1.k != -big && chck(x1, x2, x3)) {
      node *lft = nullptr, *trash = nullptr, *middle = nullptr, *rght = nullptr;
      split(roots[x], lft, middle, x2.k);
      split(middle, trash, rght, x2.k + 1);
      merge_tr(roots[x], lft, rght);
    } else {
      while (1) {
        line x3 = less_or_equal(roots[x], k.k);
        line x2 = less_or_equal(roots[x], k.k - 1);
        line x1 = less_or_equal(roots[x], x2.k - 1);
        if (x1.k == -big) break;
        if (chck(x1, x2, x3)) {
          node *lft = nullptr, *trash = nullptr, *middle = nullptr,
               *rght = nullptr;
          split(roots[x], lft, middle, x2.k);
          split(middle, trash, rght, x2.k + 1);
          merge_tr(roots[x], lft, rght);
        } else
          break;
      }
      while (1) {
        line x1 = less_or_equal(roots[x], k.k);
        line x2 = bigger(roots[x], k.k);
        line x3 = bigger(roots[x], x2.k);
        if (x2.k == -big || x3.k == -big) break;
        if (chck(x1, x2, x3)) {
          node *lft = nullptr, *trash = nullptr, *middle = nullptr,
               *rght = nullptr;
          split(roots[x], lft, middle, x2.k);
          split(middle, trash, rght, x2.k + 1);
          merge_tr(roots[x], lft, rght);
        } else
          break;
      }
    }
  }
  if (l == r) return;
  int mid = (r + l) / 2;
  if (y <= mid)
    add(x * 2, l, mid, y, k);
  else
    add(x * 2 + 1, mid + 1, r, y, k);
}
long long mn;
void findmin(node *root, int x) {
  if (root == nullptr) return;
  long long k1 = ff(x, (line){root->key, root->b});
  mn = min(mn, k1);
  if (root->rs != nullptr) {
    line x1 = get(root->rs);
    long long k2 = ff(x, x1);
    if (k1 >= k2)
      findmin(root->rs, x);
    else
      findmin(root->ls, x);
  } else if (root->ls != nullptr)
    findmin(root->ls, x);
}
void findmn(int x, int l, int r, int ll, int rr, int z) {
  if (ll <= l && r <= rr) {
    findmin(roots[x], z);
    return;
  }
  int mid = (r + l) / 2;
  if (ll <= mid) findmn(x * 2, l, mid, ll, rr, z);
  if (rr > mid) findmn(x * 2 + 1, mid + 1, r, ll, rr, z);
}
void preprocess(int x, int y) {
  t++;
  tin[x] = t;
  for (int i = 0; i < ed[x].size(); i++) {
    int to = ed[x][i];
    if (to == y) continue;
    preprocess(to, x);
  }
  tout[x] = t;
}
void dfs(int x, int y) {
  int q = 0;
  for (int i = 0; i < ed[x].size(); i++) {
    int to = ed[x][i];
    if (to == y) continue;
    q++;
    dfs(to, x);
  }
  mn = 1e18;
  findmn(1, 1, n, tin[x], tout[x], a[x]);
  if (q == 0)
    f[x] = 0;
  else
    f[x] = mn;
  add(1, 1, n, tin[x], (line){b[x], f[x]});
}
int main() {
  scanf("%d", &n);
  srand(time(NULL));
  for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
  for (int i = 1; i <= n; i++) scanf("%d", &b[i]);
  for (int i = 1; i < n; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    ed[u].push_back(v);
    ed[v].push_back(u);
  }
  preprocess(1, 0);
  dfs(1, 0);
  for (int i = 1; i <= n; i++) printf("%lld ", f[i]);
  printf("\n");
  return 0;
}
