#include <bits/stdc++.h>
using namespace std;
template <typename F, typename U>
ostream& operator<<(ostream& os, const pair<F, U>& p) {
  os << "(" << p.first << "," << p.second << ")";
  return os;
}
template <typename F>
ostream& operator<<(ostream& os, const vector<F>& v) {
  os << "[";
  for (__typeof((v).begin()) i = (v).begin(); i != (v).end(); ++i) {
    if (i != v.begin()) os << ", ";
    os << *i;
  }
  os << "]";
  return os;
}
int m;
const int MOD = 1000000007;
void add(int& a, int b) {
  a += b;
  if (a >= MOD) a -= MOD;
}
void read_number(vector<int>& A) {
  int el;
  scanf("%d", &el);
  A.clear();
  A.resize(el);
  for (int i = 0; i < (int)(el); ++i) scanf("%d", &A[i]);
}
int cnt_nodes = 0;
struct Node;
struct Node {
  int index, cost;
  vector<Node*> next;
  Node* fail;
  Node() : index(cnt_nodes++), cost(0), next(m, (Node*)NULL), fail(NULL) {}
};
Node* ground;
Node* root;
void add_string(const vector<int>& A, int cost) {
  Node* x = root;
  for (int i = 0; i < (int)(((int)((A).size()))); ++i) {
    if (x->next[A[i]] == NULL) x->next[A[i]] = new Node();
    x = x->next[A[i]];
  }
  x->cost += cost;
}
vector<vector<int> > F;
vector<vector<int> > C;
void compute_fail_links() {
  F.clear();
  F.resize(cnt_nodes, vector<int>(m, -1));
  C.clear();
  C.resize(cnt_nodes, vector<int>(m, 0));
  root->fail = ground;
  queue<Node*> Q;
  Q.push(root);
  while (!Q.empty()) {
    Node* x = Q.front();
    Q.pop();
    for (int i = 0; i < (int)(m); ++i) {
      if (x->next[i] != NULL) {
        Node* y = x->fail;
        while (y->next[i] == NULL) y = y->fail;
        x->next[i]->fail = y->next[i];
        x->next[i]->cost += y->next[i]->cost;
        Q.push(x->next[i]);
      }
      Node* y = x;
      while (y->next[i] == NULL) y = y->fail;
      F[x->index][i] = y->next[i]->index;
      C[x->index][i] = y->next[i]->cost;
    }
  }
}
int solve(const vector<int>& V, int k) {
  vector<vector<int> > D_lt(cnt_nodes, vector<int>(k + 1, 0));
  vector<vector<int> > D_eq(cnt_nodes, vector<int>(k + 1, 0));
  vector<vector<int> > D_gt(cnt_nodes, vector<int>(k + 1, 0));
  D_eq[root->index][0] = 1;
  int res = 0;
  for (int vi = 0; vi < (int)(((int)((V).size()))); ++vi) {
    vector<vector<int> > T_lt(cnt_nodes, vector<int>(k + 1, 0));
    vector<vector<int> > T_eq(cnt_nodes, vector<int>(k + 1, 0));
    vector<vector<int> > T_gt(cnt_nodes, vector<int>(k + 1, 0));
    for (int i = (int)(1); i <= (int)(cnt_nodes - 1); ++i)
      for (int s = (int)(0); s <= (int)(k); ++s)
        for (int j = 0; j < (int)(m); ++j) {
          if (vi == 0 && j == 0) continue;
          int ni = F[i][j];
          int ns = s + C[i][j];
          if (ns > k) continue;
          add(T_lt[ni][ns], D_lt[i][s]);
          if (j < V[vi]) {
            add(T_lt[ni][ns], D_eq[i][s]);
          } else if (j == V[vi]) {
            add(T_eq[ni][ns], D_eq[i][s]);
          } else {
            add(T_gt[ni][ns], D_eq[i][s]);
          }
          add(T_gt[ni][ns], D_gt[i][s]);
        }
    for (int i = (int)(1); i <= (int)(cnt_nodes - 1); ++i)
      for (int s = (int)(0); s <= (int)(k); ++s) {
        add(res, T_lt[i][s]);
        add(res, T_eq[i][s]);
        if (vi < ((int)((V).size())) - 1) add(res, T_gt[i][s]);
      }
    D_lt.swap(T_lt);
    D_eq.swap(T_eq);
    D_gt.swap(T_gt);
  }
  return res;
}
int main() {
  int n, k;
  scanf("%d%d%d", &n, &m, &k);
  vector<int> U, V;
  read_number(U);
  read_number(V);
  for (int i = (int)(((int)((U).size())) - 1); i >= (int)(0); --i)
    if (U[i] > 0) {
      --U[i];
      break;
    } else {
      U[i] = m - 1;
    }
  ground = new Node();
  root = new Node();
  for (int i = 0; i < (int)(m); ++i) ground->next[i] = root;
  for (int i = 0; i < (int)(n); ++i) {
    vector<int> S;
    read_number(S);
    int cost;
    scanf("%d", &cost);
    add_string(S, cost);
  }
  compute_fail_links();
  int res = solve(V, k);
  if (!U.empty()) res = (res - solve(U, k) + MOD) % MOD;
  printf("%d\n", res);
}
