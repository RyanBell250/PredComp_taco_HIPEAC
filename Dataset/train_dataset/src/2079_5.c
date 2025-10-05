#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <iostream>
#include <complex>
#include <string>
#include <algorithm>
#include <numeric>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <functional>
#include <cassert>
typedef long long ll;
using namespace std;
#define debug(x) cerr << __LINE__ << " : " << #x << " = " << (x) << endl;
#define mod 1000000007 
#define INF 1000000000 
#define LLINF 2000000000000000000LL 
#define SIZE 100010
struct BIT{
  typedef int Type;
  int bit_size;
  vector<Type> data;
  BIT(int n){
    bit_size = n;
    data.assign(n+2, 0);
  }
  void add(int k, Type x){
    k++;
    while(k <= bit_size){
      data[k] += x;
      k += k & (-k);
    }
  }
  Type query(int k){
    k++;
    Type rec = 0;
    while(k > 0){
      rec += data[k];
      k -= k & (-k);
    }
    return rec;
  }
};
int main(){
  int n;
  ll K;
  int a[SIZE];
  scanf("%d%lld", &n, &K);
  K = (ll)n*(n+1)/2 - K + 1;
  a[0] = 0;
  for(int i=1;i<=n;i++){
    scanf("%d", a+i);
    a[i] ^= a[i-1];
  }
  int ans = 0;
  ll sum = 0;
  int mask = 0;
  for(int i=19;i>=0;i--){
    BIT bit(1<<20);
    int next_ans = ans + (1<<i);
    ll p = 0;
    mask += 1 << i;
    for(int j=n;j>=0;j--){
      int t = (a[j] & mask) ^ ans;
      int s = t + (1 << i);
      p += bit.query(s-1) - bit.query(t-1);
      bit.add(a[j], 1);
    }
    if(p + sum < K){
      sum += p;
      ans = next_ans;
    }
  }
  cout << ans << endl;
  return 0;
}
