#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <algorithm>
#include <sstream>
#include <cmath>
#include <set>
#include <iomanip>
#include <deque>
#include <limits>
using namespace std;
typedef long long ll;
 
#define REP(i,n) for(int (i)=0;(i)<(int)(n);(i)++)
#define RREP(i,n) for(int (i)=(int)(n)-1;i>=0;i--)
#define FOREACH(i,Itr) for(auto (i)=(Itr).begin();(i)!=(Itr).end();(i)++)
#define REMOVE(Itr,n) (Itr).erase(remove((Itr).begin(),(Itr).end(),n),(Itr).end())
#define UNIQUE(Itr) sort((Itr).begin(),(Itr).end()); (Itr).erase(unique((Itr).begin(),(Itr).end()),(Itr).end())
#define LBOUND(Itr,val) lower_bound((Itr).begin(),(Itr).end(),(val))
#define UBOUND(Itr,val) upper_bound((Itr).begin(),(Itr).end(),(val))

template <class T> struct RangeAddFenwickTree {

   vector<T> node1, node2;
   RangeAddFenwickTree (int n) : node1(n,0), node2(n,0) {}

    void add(int l, int r, T val) {
      for (int i = l; i <= node1.size(); i += i & -i) {
         node1[i] += -l * val;
         node2[i] += val;
      }
      for (int i = r; i <= node1.size(); i += i & -i) {
         node1[i] += r * val;
         node2[i] += -val;
      }
   }

   T sum(int idx) {
      T sum1 = 0, sum2 = 0;
      for (int i = idx; i > 0; i &= (i - 1)) {
         sum1 += node1[i];
         sum2 += node2[i] * idx;
      }
      return sum1 + sum2;
   }

};

int main() {

  int n,q; cin >> n >> q;

  RangeAddFenwickTree<ll> inst(100010);
  REP(i,q) {
    ll com,s,t,x;
    cin >> com;
    if(com == 0) {
      cin >> s >> t >> x;
      inst.add(s,t+1,x);
    } else {
      cin >> s >> t;
      cout << inst.sum(t+1) - inst.sum(s) << endl;
    }
  }
 
  return 0;
}