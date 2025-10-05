#include <bits/stdc++.h>
#pragma GCC optimize(2)
using namespace std;
queue<int> que_init;
vector<int> vec[200010];
bool vis[200010];
int size_tree_read[200010], __G, color[200010], Deep[200010], cnt_this,
    Size_all, Minsize, n, m, T, Len, Every_letter_end_for_AC[200010],
    Every_letter_end_rev_AC[200010], tmp_pos_SAM_for[200010],
    tmp_pos_SAM_rev[200010];
long long ans[200010];
char str1[200030], str[200030];
struct graph {
  int val[200010], cnt, Next[200010], head[200010], Key[200010];
  void add(int a, int b, int c) {
    val[++cnt] = b;
    Next[cnt] = head[a];
    head[a] = cnt;
    Key[cnt] = c;
  }
} graph_read, graph_AC;
struct Automaton {
  int Size_AC, child_AC[200010][26], fail_AC[200010], root_Trie, In_AC[200010],
      Out_AC[200010], Endpos_tmp[200010];
  int Endpos[200010], Size_SAM, root_SAM, child_SAM[200010][26],
      father_SAM[200010], Max_SAM[200010], child_ST[200010][26], In_ST[200010],
      Out_ST[200010], pos_SAM[200010];
  int tim;
  int Trie_insert(int flag, int len, int st) {
    int now = 0;
    if (!flag) {
      for (int i = 1; i <= len; i++) {
        if (!child_AC[now][str1[i] - 'a'])
          child_AC[now][str1[i] - 'a'] = ++Size_AC;
        now = child_AC[now][str1[i] - 'a'];
        Endpos_tmp[now] = st + i - 1;
        Every_letter_end_for_AC[st + i - 1] = now;
      }
    } else {
      for (int i = len; i >= 1; i--) {
        if (!child_AC[now][str1[i] - 'a'])
          child_AC[now][str1[i] - 'a'] = ++Size_AC;
        now = child_AC[now][str1[i] - 'a'];
        Endpos_tmp[now] = st + i - 1;
        Every_letter_end_rev_AC[st + i - 1] = now;
      }
    }
    return now;
  }
  void SAM_insert(int p, int c, int endpos, int x) {
    int np = ++Size_SAM;
    Max_SAM[np] = Max_SAM[p] + 1;
    pos_SAM[x] = np;
    Endpos[np] = endpos;
    for (; p && !child_SAM[p][c]; p = father_SAM[p]) child_SAM[p][c] = np;
    if (!p)
      father_SAM[np] = root_SAM;
    else {
      int q = child_SAM[p][c];
      if (Max_SAM[p] + 1 == Max_SAM[q])
        father_SAM[np] = q;
      else {
        int nq = ++Size_SAM;
        Endpos[nq] = endpos;
        Max_SAM[nq] = Max_SAM[p] + 1;
        father_SAM[nq] = father_SAM[q];
        memcpy(child_SAM[nq], child_SAM[q], sizeof(child_SAM[nq]));
        father_SAM[q] = father_SAM[np] = nq;
        for (; p && child_SAM[p][c] == q; p = father_SAM[p])
          child_SAM[p][c] = nq;
      }
    }
  }
  void ST_dfs(int u) {
    In_ST[u] = ++tim;
    for (int i = 0; i < 26; i++)
      if (child_ST[u][i]) ST_dfs(child_ST[u][i]);
    Out_ST[u] = tim;
  }
  void AC_dfs(int u) {
    In_AC[u] = ++tim;
    for (int i = graph_AC.head[u]; i; i = graph_AC.Next[i]) {
      int v = graph_AC.val[i];
      AC_dfs(v);
    }
    Out_AC[u] = tim;
  }
  void init(int flag) {
    fail_AC[0] = 0;
    pos_SAM[0] = 1;
    que_init.push(0);
    root_SAM = ++Size_SAM;
    while (!que_init.empty()) {
      int u = que_init.front();
      que_init.pop();
      for (int i = 0; i < 26; i++)
        if (u == 0) {
          if (!child_AC[u][i])
            child_AC[u][i] = 0;
          else
            fail_AC[child_AC[u][i]] = 0, que_init.push(child_AC[u][i]),
            SAM_insert(pos_SAM[u], i, Endpos_tmp[child_AC[u][i]],
                       child_AC[u][i]);
        } else {
          if (!child_AC[u][i])
            child_AC[u][i] = child_AC[fail_AC[u]][i];
          else
            fail_AC[child_AC[u][i]] = child_AC[fail_AC[u]][i],
            que_init.push(child_AC[u][i]),
            SAM_insert(pos_SAM[u], i, Endpos_tmp[child_AC[u][i]],
                       child_AC[u][i]);
        }
    }
    for (int i = 2; i <= Size_SAM; i++)
      child_ST[father_SAM[i]]
              [str[(flag) ? (Endpos[i] + Max_SAM[father_SAM[i]])
                          : (Endpos[i] - Max_SAM[father_SAM[i]])] -
               'a'] = i;
    graph_AC.cnt = 0;
    memset(graph_AC.head, 0, sizeof(graph_AC.head));
    for (int i = 1; i <= Size_AC; i++) graph_AC.add(fail_AC[i], i, 0);
    tim = 0;
    ST_dfs(1);
    tim = 0;
    AC_dfs(0);
  }
} Forward, Reverse;
struct status {
  int pos_for_st, pos_rev_st, pos_for_AC, pos_rev_AC, available_len_for_st,
      available_len_rev_st;
  bool fail_for_st, fail_rev_st;
  status() {
    pos_for_st = pos_rev_st = 1;
    pos_for_AC = pos_rev_AC = available_len_for_st = available_len_rev_st =
        fail_for_st = fail_rev_st = 0;
  }
} Sta[200010][20];
struct query_node {
  int u, v, x, id, flag;
} question[200010];
struct BIT {
  int tree[200010];
  void change(int x, int key) {
    for (; x <= 200000; x += x & (-x)) tree[x] += key;
  }
  int query(int x) {
    int ans = 0;
    for (; x; x -= x & (-x)) ans += tree[x];
    return ans;
  }
  int query_interval(int l, int r) { return query(r) - query(l - 1); }
} BIT_for, BIT_rev, BIT_2D;
struct node1 {
  int x, y, key;
} point[1000010];
int st[200010], ed[200010], For_end_in_AC[200010], Rev_end_in_AC[200010];
int read() {
  int ans = 0;
  char ch = getchar();
  while (ch < '0' || ch > '9') ch = getchar();
  while (ch >= '0' && ch <= '9') ans = ans * 10 + ch - '0', ch = getchar();
  return ans;
}
bool cmp(query_node a, query_node b) { return a.x < b.x; }
bool cmp1(query_node a, query_node b) { return a.flag < b.flag; }
bool cmp2(node1 a, node1 b) {
  if (a.x < b.x)
    return true;
  else if (a.x == b.x) {
    if (a.y < b.y)
      return true;
    else if (a.y == b.y)
      return a.key < b.key;
    else
      return false;
  } else
    return false;
}
void DP(int u, int fa) {
  size_tree_read[u] = 1;
  for (int i = graph_read.head[u]; i; i = graph_read.Next[i]) {
    int v = graph_read.val[i];
    if (v == fa || vis[v]) continue;
    DP(v, u);
    size_tree_read[u] += size_tree_read[v];
  }
}
void calcG(int u, int fa) {
  int Max = 0;
  for (int i = graph_read.head[u]; i; i = graph_read.Next[i]) {
    int v = graph_read.val[i];
    if (v == fa || vis[v]) continue;
    calcG(v, u);
    Max = max(Max, size_tree_read[v]);
  }
  Max = max(Max, Size_all - size_tree_read[u]);
  if (Max < Minsize) __G = u, Minsize = Max;
}
int getG(int u) {
  DP(u, 0);
  Size_all = size_tree_read[u];
  __G = 0;
  Minsize = 1e9;
  calcG(u, 0);
  return __G;
}
status transfer(status x, int c) {
  if (!x.fail_for_st) {
    if (x.available_len_for_st == Forward.Max_SAM[x.pos_for_st]) {
      if (Forward.child_ST[x.pos_for_st][c])
        x.pos_for_st = Forward.child_ST[x.pos_for_st][c],
        x.available_len_for_st++;
      else
        x.fail_for_st = true;
    } else {
      if (str[Forward.Endpos[x.pos_for_st] - x.available_len_for_st] - 'a' == c)
        x.available_len_for_st++;
      else
        x.fail_for_st = true;
    }
  }
  if (!x.fail_rev_st) {
    if (x.available_len_rev_st == Reverse.Max_SAM[x.pos_rev_st]) {
      if (Reverse.child_ST[x.pos_rev_st][c])
        x.pos_rev_st = Reverse.child_ST[x.pos_rev_st][c],
        x.available_len_rev_st++;
      else
        x.fail_rev_st = true;
    } else {
      if (str[Reverse.Endpos[x.pos_rev_st] + x.available_len_rev_st] - 'a' == c)
        x.available_len_rev_st++;
      else
        x.fail_rev_st = true;
    }
  }
  x.pos_for_AC = Forward.child_AC[x.pos_for_AC][c];
  x.pos_rev_AC = Reverse.child_AC[x.pos_rev_AC][c];
  return x;
}
void Give_color(int u, int fa, int col, int deep, int c) {
  color[u] = col;
  if (u == 277 && deep == 0) u = 277;
  Sta[u][deep] = transfer(Sta[fa][deep], c);
  for (int i = graph_read.head[u]; i; i = graph_read.Next[i]) {
    int v = graph_read.val[i];
    if (v == fa || vis[v]) continue;
    Give_color(v, u, col, deep, graph_read.Key[i]);
  }
}
void getans(int u, int fa, int deep) {
  BIT_for.change(Forward.In_AC[Sta[u][deep].pos_for_AC], 1);
  BIT_rev.change(Reverse.In_AC[Sta[u][deep].pos_rev_AC], 1);
  for (int i = 0; i < (int)vec[u].size(); i++)
    if (vec[u][i] > 0)
      ans[question[vec[u][i]].id] += BIT_rev.query_interval(
          Reverse.In_AC[Rev_end_in_AC[question[vec[u][i]].x]],
          Reverse.Out_AC[Rev_end_in_AC[question[vec[u][i]].x]]);
    else
      ans[question[-vec[u][i]].id] += BIT_for.query_interval(
          Forward.In_AC[For_end_in_AC[question[-vec[u][i]].x]],
          Forward.Out_AC[For_end_in_AC[question[-vec[u][i]].x]]);
  vec[u].clear();
  for (int i = graph_read.head[u]; i; i = graph_read.Next[i]) {
    int v = graph_read.val[i];
    if (vis[v] || v == fa) continue;
    getans(v, u, deep);
  }
  BIT_for.change(Forward.In_AC[Sta[u][deep].pos_for_AC], -1);
  BIT_rev.change(Reverse.In_AC[Sta[u][deep].pos_rev_AC], -1);
}
void solve_no_changedir(int u, int deep, int L, int R) {
  if (L > R) return;
  int G = getG(u);
  vis[G] = true;
  color[G] = 0;
  Deep[G] = deep;
  int color_num = 0;
  for (int i = graph_read.head[G]; i; i = graph_read.Next[i]) {
    int v = graph_read.val[i];
    if (vis[v]) continue;
    Give_color(v, G, ++color_num, deep, graph_read.Key[i]);
  }
  for (int i = L; i <= R; i++)
    if (color[question[i].u] == color[question[i].v])
      question[i].flag = color[question[i].u];
    else
      question[i].flag = 0;
  sort(question + L, question + R + 1, cmp1);
  int j = L;
  for (; j <= R && question[j].flag == 0; j++) {
    question[j].flag = G;
    vec[question[j].u].push_back(j);
    vec[question[j].v].push_back(-j);
  }
  for (int i = graph_read.head[G]; i; i = graph_read.Next[i]) {
    int v = graph_read.val[i];
    if (vis[v]) continue;
    getans(v, G, deep);
  }
  if (j > R) return;
  for (int i = graph_read.head[G]; i; i = graph_read.Next[i]) {
    int v = graph_read.val[i];
    if (vis[v]) continue;
    if (color[v] != question[j].flag) continue;
    int tmp = j;
    while (j <= R && question[j].flag == color[v]) j++;
    solve_no_changedir(v, deep + 1, tmp, j - 1);
    if (j > R) break;
  }
}
void Create_interval(int l1, int r1, int l2, int r2) {
  point[++cnt_this] = (node1){l1, l2, 1};
  point[++cnt_this] = (node1){l1, r2 + 1, -1};
  point[++cnt_this] = (node1){r1 + 1, l2, -1};
  point[++cnt_this] = (node1){r1 + 1, r2 + 1, 1};
}
int main() {
  n = read();
  m = read();
  T = read();
  for (int i = 1; i < n; i++) {
    int u = read(), v = read();
    char c = getchar();
    graph_read.add(u, v, c - 'a');
    graph_read.add(v, u, c - 'a');
  }
  for (int i = 1; i <= m; i++) {
    scanf("%s", str1 + 1);
    st[i] = Len + 1;
    int len = strlen(str1 + 1);
    for (int j = 1; j <= len; j++) str[++Len] = str1[j];
    ed[i] = Len;
    For_end_in_AC[i] = Forward.Trie_insert(0, len, st[i]);
    Rev_end_in_AC[i] = Reverse.Trie_insert(1, len, st[i]);
  }
  Forward.init(0);
  Reverse.init(1);
  for (int i = 1; i <= Len; i++) {
    tmp_pos_SAM_for[i] = Forward.pos_SAM[Every_letter_end_for_AC[i]];
    tmp_pos_SAM_rev[i] = Reverse.pos_SAM[Every_letter_end_rev_AC[i]];
  }
  for (int i = 1; i <= T; i++)
    question[i].u = read(), question[i].v = read(), question[i].x = read(),
    question[i].id = i;
  solve_no_changedir(1, 0, 1, T);
  sort(question + 1, question + T + 1, cmp);
  int now_query = 1, now_str = 1;
  while (now_query <= T) {
    if (question[now_query].x != now_str) {
      now_str++;
      continue;
    }
    cnt_this = 0;
    for (int i = st[now_str]; i < ed[now_str]; i++)
      Create_interval(Forward.In_ST[tmp_pos_SAM_for[i]],
                      Forward.Out_ST[tmp_pos_SAM_for[i]],
                      Reverse.In_ST[tmp_pos_SAM_rev[i + 1]],
                      Reverse.Out_ST[tmp_pos_SAM_rev[i + 1]]);
    while (now_query <= T && question[now_query].x == now_str) {
      status x = Sta[question[now_query].u][Deep[question[now_query].flag]],
             y = Sta[question[now_query].v][Deep[question[now_query].flag]];
      if (x.available_len_for_st < Forward.Max_SAM[x.pos_for_st])
        x.pos_for_st = Forward.father_SAM[x.pos_for_st];
      if (y.available_len_rev_st < Reverse.Max_SAM[y.pos_rev_st])
        y.pos_rev_st = Reverse.father_SAM[y.pos_rev_st];
      point[++cnt_this] = (node1){Forward.In_ST[x.pos_for_st],
                                  Reverse.In_ST[y.pos_rev_st], now_query + 1};
      now_query++;
    }
    sort(point + 1, point + cnt_this + 1, cmp2);
    for (int i = 1; i <= cnt_this; i++)
      if (point[i].key < 2)
        BIT_2D.change(point[i].y, point[i].key);
      else
        ans[question[point[i].key - 1].id] += BIT_2D.query(point[i].y);
    for (int i = 1; i <= cnt_this; i++)
      if (point[i].key < 2) BIT_2D.change(point[i].y, -point[i].key);
    now_str++;
  }
  for (int i = 1; i <= T; i++) printf("%lld\n", ans[i]);
  return 0;
}
