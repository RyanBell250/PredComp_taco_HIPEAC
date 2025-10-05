#include<bits/stdc++.h>

#define rep(i,n) for(ll i=0;i<(n);i++)
#define all(c) (c).begin(),(c).end()

using namespace std;
typedef long long ll;

bool is_uruu(ll y)
{
  return (y%4==0&&y%100!=0)||(y%400==0);
}

ll fairfield(ll y,ll m,ll d) {
  if(m<=2) y--,m+=12;
  ll t= 365LL*(y%7)+y/4-y/100+y/400+153*(m+1)/5+d-428;
  while(t<=0) t+=7;
  return t;
}
ll ans=0;
ll cnt=688;

ll func(ll y1,ll m1,ll d1,ll y2,ll m2,ll d2) {
  ll dd[]={0,31,28,31,30,31,30,31,31,30,31,30,31};
  ll c=0;
  for(ll y = y1;y <= y2; y++) {
    ll m_st = 1, m_end=12;
    if(y == y1) 
      m_st = m1;
    if(y == y2) 
      m_end = m2;
    for(ll m = m_st; m <= m_end; m++) {
      ll d_st = 1, d_end = dd[m];
      if(m == 2 && is_uruu(y)) 
        d_end++;
      if(y == y1 && m == m1) 
        d_st = d1;
      if(y == y2 && m == m2) 
        d_end = d2;
      for(ll d = d_st; d <= d_end; d++) {
        if(d == 13 && fairfield(y,m,d) % 7 == 5) c++;
      }
    }
  }
  return c;
}

int main()
{
  ll y1,m1,d1;
  ll y2,m2,d2;

	cin >> y1 >> m1 >> d1 >> y2 >> m2 >> d2;
	ll y_fir, y_sec;
	y_fir = y1 + 400L - (y1 % 400L);
	y_sec = y2 - y2 % 400L;
  if(y_fir >= y2)
    cout << func(y1, m1, d1, y2, m2, d2) << endl;
  else
    cout <<	func(y1, m1, d1, y_fir-1, 12, 31) + func(y_sec, 1, 1, y2, m2, d2) + (y_sec - y_fir)/400 * func(400, 1, 1, 799, 12, 31) << endl;
}
