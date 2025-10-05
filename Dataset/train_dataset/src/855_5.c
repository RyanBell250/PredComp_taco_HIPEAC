#include <bits/stdc++.h>
#define REP(i,n) for(int i=0;i<(int)(n);i++)
#define FOR(i,k,n) for(int i=(k);i<(int)(n);i++)
#define getb(j) ((bits>>(j))&1)
using namespace std;
const int mod = 1000000007;
struct Mod {
  int num;
  Mod () : num(0) {;}
  Mod (int n) : num(n) {;}
  operator int() { return num; }
};
Mod operator+(Mod a, Mod b) { return Mod((a.num + b.num) % mod); }
Mod operator-(Mod a, Mod b) { return Mod((mod + a.num - b.num) % mod); }
Mod operator*(Mod a, Mod b) { return Mod(((long long)a.num * b.num) % mod); }
Mod operator+=(Mod &a, Mod b) { return a = a + b; }
Mod operator-=(Mod &a, Mod b) { return a = a - b; }
typedef array<Mod, 9> Array;
typedef array<Array, 9> Matrix;
typedef array<Matrix, 2> Cube;
typedef array<Cube, 2> DPTable;
typedef tuple<int,int,int,int> J;
int K;
struct UnionFind {
  vector<int> parent;
  UnionFind (int n) { parent.assign(n, -1); }
  int root(int x) { return parent[x] < 0 ? x : parent[x] = root(parent[x]); }
  bool merge(int x, int y) {
    x = root(x); y = root(y);
    if (x == y) return false;
    if (parent[y] < parent[x]) swap(x, y);
    if (parent[x] == parent[y]) --parent[x];
    parent[y] = x;
    return true;
  }
};
shared_ptr<DPTable> step_normal(const shared_ptr<DPTable> &prev_dp, bool is_cn) {
  shared_ptr<DPTable> dp = make_shared<DPTable>();
  REP(i,1<<4) {
    bitset<4> bs(i);
    UnionFind uf(4);
    int ary[3][2] = {{0,1},{0,2},{1,3}};
    REP(j,3) if (bs[ary[j][0]] == bs[ary[j][1]]) uf.merge(ary[j][0], ary[j][1]);
    if (is_cn && bs[2] == bs[3]) uf.merge(2,3);
    REP(p1,K+1)REP(p2,K+1) {
      int cnt[4] = {0};
      ++cnt[uf.root(0)];
      ++cnt[uf.root(1)];
      cnt[uf.root(2)] += p1;
      cnt[uf.root(3)] += p2;
      bool ok = true;
      REP(j,4) if (cnt[j] > K) ok = false;
      if (!ok) break;
      if (bs[0] == bs[1])
        (*dp)[bs[0]][bs[1]][cnt[uf.root(0)]][0] += (*prev_dp)[bs[2]][bs[3]][p1][p2];
      else
        (*dp)[bs[0]][bs[1]][cnt[uf.root(0)]][cnt[uf.root(1)]] += (*prev_dp)[bs[2]][bs[3]][p1][p2];
    }
  }
  return dp;
}
shared_ptr<DPTable> step_junction(const array<shared_ptr<DPTable>, 3> &children, const bool is_cn) {
  shared_ptr<DPTable> dp = make_shared<DPTable>();
  REP(i,1<<5){
    const int bits = i<<1;
    bitset<6> bs(bits);
    UnionFind uf(6);
    int ary[6][2] = {{0,1},{2,3},{0,3},{1,2},{1,4},{2,5}};
    REP(j,6)
      if (bs[ary[j][0]] == bs[ary[j][1]])
        uf.merge(ary[j][0], ary[j][1]);
    if (is_cn && bs[4] == bs[5])
      uf.merge(4, 5);
    int ufr[6];
    REP(j,6) ufr[j] = uf.root(j);
    int powK1[7];
    powK1[0] = 1;
    REP(j,6) powK1[j+1] = powK1[j] * (K+1);
    int loop = powK1[6];
    if (is_cn && bs[4] == bs[5]) loop = powK1[5];
    REP(j,loop) {
      int pi[6];
      int cnt[6] = {0};
      int ind = j;
      REP(k,6){
        pi[k] = ind%(K+1);
        ind /= K+1;
        cnt[ufr[k]] += pi[k];
      }
      if (!getb(1) && pi[0]) {
        j = (j / powK1[1]) * powK1[1] + (powK1[1] - 1);
        continue;
      } else if (getb(2) == getb(3) && pi[2]) {
        j = (j / powK1[3]) * powK1[3] + (powK1[3] - 1);
        continue;
      } else if (!is_cn) {
        if (pi[4] > 1) {
          j = (j / powK1[5]) * powK1[5] + (powK1[5] - 1);
          continue;
        } else if (pi[5] > 1) {
          break;
        }
      }
      bool ok = true;
      REP(k,6) if (cnt[k] > K) ok = false;
      if (!ok) {
        int k = 1;
        while((j % powK1[k]) == 0) ++k;
        j = (j / powK1[k]) * powK1[k] + (powK1[k] - 1);
        continue;
      }
      Mod addv = (*children[0])[getb(4)][getb(5)][pi[4]][pi[5]]
        * (*children[1])[getb(1)][0][pi[1]][pi[0]]
        * (*children[2])[getb(3)][getb(2)][pi[3]][pi[2]];
      if (!getb(3))
        (*dp)[0][getb(3)][cnt[ufr[0]]][0] += addv;
      else
        (*dp)[0][getb(3)][cnt[ufr[0]]][cnt[ufr[3]]] += addv;
    }
  }
  REP(i,2)REP(j,K+1)REP(k,K+1) {
    (*dp)[1][i][j][k] = (*dp)[0][1-i][j][k];
  }
  return dp;
}
pair<shared_ptr<DPTable>, bool> calc(const vector<int>& len, const vector<J>& jct, int index, int p, int d) {
  if (p == 0 || p == len[index]-1) { 
    shared_ptr<DPTable> dp = make_shared<DPTable>();
    if (p+d < 0 || p+d >= len[index]) {
      REP(i,2)REP(j,2) (*dp)[i][j][1][1] = 1;
    } else {
      auto child = *(calc(len,jct,index,p+d,d).first);
      REP(i,2)REP(j,2)REP(k,2)REP(l,2){
        UnionFind uf(4);
        if (i==k) uf.merge(0,2);
        if (j==l) uf.merge(1,3);
        if (k==l) uf.merge(2,3);
        REP(m,K+1)REP(n,K+1) {
          int w[4] = {1,1,m,n};
          map<int,int> mp;
          REP(o,4) mp[uf.root(o)] += w[o];
          int r0 = mp[uf.root(0)];
          int r1 = mp[uf.root(1)];
          if (r0 > K || r1 > K) continue;
          (*dp)[i][j][r0][r1] += child[k][l][m][n];
        }
      }
    }
    return make_pair(dp, false);
  } else { 
    REP(i,jct.size()) {
      int f,p1,t,p2;
      tie(f,p1,t,p2) = jct[i];
      if (index == t) {
        swap(f,t); swap(p1,p2);
      }
      if (index == f) {
        if (min(p, p+d) == p1) {
          array<shared_ptr<DPTable>, 3> children;
          bool is_cn;
          tie(children[0], is_cn) = calc(len,jct,index,p+2*d,d);
          if (d>0) {
            children[1] = calc(len,jct,t,p2,-1).first;
            children[2] = calc(len,jct,t,p2+1,1).first;
          } else {
            children[1] = calc(len,jct,t,p2+1,1).first;
            children[2] = calc(len,jct,t,p2,-1).first;
          }
          return make_pair(step_junction(children, is_cn), true);
        }
      }
    }
    auto child = calc(len,jct,index,p+d,d);
    return make_pair(step_normal(child.first, child.second), true);
  }
}
int main() {
  while(1) {
    int n;
    cin>>n>>K;
    if(!n) break;
    vector<int> l(n);
    REP(i,n) {
      cin>>l[i];
      l[i] += 3;
    }
    vector<J> jct;
    REP(i,n-1) {
      int f,p,t,q;
      cin>>f>>p>>t>>q;
      ++p;++q;
      jct.emplace_back(f,p,t,q);
    }
    auto res = calc(l,jct,0,0,1).first;
    Mod sum = 0;
    REP(i,2)REP(j,2)REP(k,K+1)REP(l,K+1) {
      sum += (*res)[i][j][k][l];
    }
    cout << sum << endl;
  }
  return 0;
}