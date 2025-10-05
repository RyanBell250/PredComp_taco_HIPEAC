#include <bits/stdc++.h>
using namespace std;
const long long mod = 1e9 + 7;
void __print(int x) { cerr << x; }
void __print(long x) { cerr << x; }
void __print(long long x) { cerr << x; }
void __print(unsigned x) { cerr << x; }
void __print(unsigned long x) { cerr << x; }
void __print(unsigned long long x) { cerr << x; }
void __print(double x) { cerr << x; }
void __print(long double x) { cerr << x; }
void __print(char x) { cerr << '\'' << x << '\''; }
void __print(const char *x) { cerr << '\"' << x << '\"'; }
void __print(const string &x) { cerr << '\"' << x << '\"'; }
void __print(bool x) { cerr << (x ? "true" : "false"); }
template <typename T, typename V>
void __print(const pair<T, V> &x) {
  cerr << '{';
  __print(x.first);
  cerr << ',';
  __print(x.second);
  cerr << '}';
}
template <typename T>
void __print(const T &x) {
  int f = 0;
  cerr << '{';
  for (auto &i : x) cerr << (f++ ? "," : ""), __print(i);
  cerr << "}";
}
void _print() { cerr << "]\n"; }
template <typename T, typename... V>
void _print(T t, V... v) {
  __print(t);
  if (sizeof...(v)) cerr << ", ";
  _print(v...);
}
struct node {
  long long data;
  node *next;
};
class linked_list {
 public:
  node *head, *tail;
  linked_list() {
    head = NULL;
    tail = NULL;
  }
  void add_node(long long n) {
    node *tmp = new node;
    tmp->data = n;
    tmp->next = NULL;
    if (head == NULL) {
      head = tmp;
      tail = tmp;
    } else {
      tail->next = tmp;
      tail = tail->next;
    }
  }
  void print_list() {
    node *temp = this->head;
    while (temp) {
      cerr << temp->data << " ";
      temp = temp->next;
    }
    cerr << endl;
  }
  void merge_list(node *h, node *t) {
    if (this->head != NULL && h != NULL) {
      this->tail->next = h;
      this->tail = t;
    } else {
      this->head = h;
      this->tail = t;
    }
  }
  void clear_list() {
    this->head = NULL;
    this->tail = NULL;
  }
};
void solve() {
  long long q;
  cin >> q;
  long long s = 500006;
  vector<linked_list> a(s);
  long long index = 0;
  for (long long i = 0; i < q; i++) {
    long long x;
    cin >> x;
    if (x == 1) {
      long long y;
      cin >> y;
      a[y].add_node(index);
      index++;
    } else {
      long long i, f;
      cin >> i >> f;
      vector<long long> temp;
      if (i != f) {
        if (a[i].head) {
          a[f].merge_list(a[i].head, a[i].tail);
          a[i].clear_list();
        }
      }
    }
  }
  map<long long, long long> m;
  for (long long i = 0; i < s; i++) {
    if (a[i].head != NULL) {
      node *temp = a[i].head;
      while (temp) {
        m[temp->data] = i;
        temp = temp->next;
      }
    }
  }
  for (auto x : m) {
    cout << x.second << " ";
  }
  cout << endl;
  return;
}
int main() {
  chrono::time_point<chrono::system_clock> start, end;
  start = std::chrono::system_clock::now();
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  int tt = 1;
  while (tt--) {
    solve();
  }
  end = std::chrono::system_clock::now();
  chrono::duration<double> elapsed_seconds = end - start;
  cerr << "Time: " << elapsed_seconds.count() << "s\n";
}
