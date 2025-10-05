#include <bits/stdc++.h>
using namespace std;
#define GET_MACRO(_1, _2, _3, NAME, ...) NAME
#define _repl(i,a,b) for(int i=(int)(a);i<(int)(b);i++)
#define _rep(i,n) _repl(i,0,n)
#define rep(...) GET_MACRO(__VA_ARGS__, _repl, _rep)(__VA_ARGS__)
#define mp(a,b) make_pair((a),(b))
#define pb(a) push_back((a))
#define all(x) (x).begin(),(x).end()
#define uniq(x) sort(all(x)),(x).erase(unique(all(x)),end(x))
#define fi first
#define se second
#define dbg(...) _dbg(#__VA_ARGS__, __VA_ARGS__)
void _dbg(string){cout<<endl;}
template<class H,class... T> void _dbg(string s,H h,T... t){int l=s.find(',');cout<<s.substr(0,l)<<" = "<<h<<", ";_dbg(s.substr(l+1),t...);}
template<class T,class U> ostream& operator<<(ostream &o, const pair<T,U> &p){o<<"("<<p.fi<<","<<p.se<<")";return o;}
template<class T> ostream& operator<<(ostream &o, const vector<T> &v){o<<"[";for(T t:v){o<<t<<",";}o<<"]";return o;}

#define SZ 250000
#define B 500

long a[SZ+B+5];
long b[B+5];
bool same[B+5];

inline void update(int blk){
  same[blk] = true;
  rep(i,B) same[blk] &= a[blk*B+i]==a[blk*B];
}

inline bool check(){
  rep(i,B) if(!same[i] || a[i*B]+b[i]!=0) return false;
  return true;
}

void query(int l, int r, int x){
  if(l/B == r/B){
    rep(i,l,r) a[i] += x;
    update(l/B);
  }
  else{
    rep(i,l,(l/B+1)*B) a[i] += x;
    rep(i,l/B+1,r/B) b[i] += x;
    rep(i,r/B*B, r) a[i] += x;
    update(l/B);
    update(r/B);
  }
}

int main(){
  int n;
  cin>>n;
  vector<int> s(n);
  rep(i,n) scanf("%d", &s[i]);

  fill(a, a+SZ, 0);
  fill(b, b+B, 0);
  rep(i,n/2) a[i] = s[i] - s[n-i-1];

  rep(i,B) update(i);

  int q;
  cin>>q;
  rep(_,q){
    int l,r,x;
    scanf("%d %d %d", &l, &r, &x);
    l--;

    if(r<n/2){
      query(l,r,x);
    }
    else if(l>=n/2){
      query(n-r, n-l, -x);
    }
    else{
      query(l,n/2,x);
      query(n-r,n/2,-x);
    }

    if(check()) puts("1");
    else puts("0");
  }

  return 0;
}