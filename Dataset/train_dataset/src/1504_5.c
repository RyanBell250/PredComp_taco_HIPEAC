#include <bits/stdc++.h>
using namespace std;
const int K = 6, N = 100000;
int arr[N + 2], mod = 1000000007;
long long MOD = 1LL * mod * mod;
int C[K][K];
int SumOfPowers[K][N + 2];
void fill() {
  C[0][0] = 1;
  for (int i = 1; i < K; ++i) {
    C[i][0] = 1;
    for (int j = 1; j <= i; ++j)
      C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % mod;
  }
  for (int j = 1; j <= N; ++j) SumOfPowers[0][j] = 1;
  for (int i = 1; i < K; ++i) {
    for (int j = 1; j <= N; ++j)
      SumOfPowers[i][j] = 1LL * SumOfPowers[i - 1][j] * j % mod;
  }
  for (int i = 0; i < K; ++i) {
    for (int j = 1; j <= N; ++j) {
      SumOfPowers[i][j] += SumOfPowers[i][j - 1];
      if (SumOfPowers[i][j] >= mod) SumOfPowers[i][j] -= mod;
    }
  }
}
struct tree {
  tree() : left(NULL), right(NULL), val(0), size(1), notPushed(false){};
  int ans[K], val, size;
  bool notPushed;
  tree *left, *right;
};
tree* merge(tree* l, tree* r, tree* to = NULL) {
  tree* ret = to == NULL ? new tree() : to;
  ret->left = l;
  ret->right = r;
  ret->size = l->size + r->size;
  for (int i = 0; i < K; ++i) {
    long long res = l->ans[i];
    int pw = 1, k = l->size;
    for (int j = 0; j <= i; ++j) {
      for (int t = 0; t < C[i][j]; ++t) {
        res = (res + 1LL * pw * r->ans[i - j]);
        if (res >= MOD) res -= MOD;
      }
      pw = (1LL * pw * k) % mod;
    }
    ret->ans[i] = res % mod;
  }
  return ret;
}
void setFixed(tree* root, int val) {
  if (root) {
    root->notPushed = true;
    root->val = val;
    for (int i = 0; i < K; ++i)
      root->ans[i] = 1LL * val * SumOfPowers[i][root->size] % mod;
  }
}
void push(tree* root) {
  if (root && root->notPushed) {
    root->notPushed = false;
    setFixed(root->left, root->val);
    setFixed(root->right, root->val);
    merge(root->left, root->right, root);
  }
}
tree* build(int l, int r) {
  if (l == r) {
    tree* ret = new tree();
    for (int i = 0; i < K; ++i) ret->ans[i] = arr[l];
    return ret;
  }
  int m = (l + r) >> 1;
  return merge(build(l, m), build(m + 1, r));
}
tree* find(tree* root, int l, int r, int L, int R) {
  if (l == L && r == R) return root;
  push(root);
  int m = (l + r) >> 1;
  if (R <= m) return find(root->left, l, m, L, R);
  if (L > m) return find(root->right, m + 1, r, L, R);
  return merge(find(root->left, l, m, L, m),
               find(root->right, m + 1, r, m + 1, R));
}
void update(tree* root, int l, int r, int L, int R, int val) {
  if (l == L && r == R) {
    setFixed(root, val);
    return;
  }
  push(root);
  int m = (l + r) >> 1;
  if (R <= m)
    update(root->left, l, m, L, R, val);
  else if (L > m)
    update(root->right, m + 1, r, L, R, val);
  else {
    update(root->left, l, m, L, m, val);
    update(root->right, m + 1, r, m + 1, R, val);
  }
  merge(root->left, root->right, root);
}
int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; ++i) scanf("%d", &arr[i]);
  fill();
  tree* root = build(0, n - 1);
  scanf("\n");
  for (int i = 0; i < m; ++i) {
    char c;
    int a, b, v;
    scanf("%c %d %d %d\n", &c, &a, &b, &v);
    --a;
    --b;
    if (c == '=')
      update(root, 0, n - 1, a, b, v);
    else
      printf("%d\n", find(root, 0, n - 1, a, b)->ans[v]);
  }
  return 0;
}
