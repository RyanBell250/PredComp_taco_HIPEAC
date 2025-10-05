#include <bits/stdc++.h>
using namespace std;
int main() {
  long n,x,m,ans=0;
  bool aaa=false;
  cin >> n >> x >> m;
  vector<long> a(5000000),aruisekiwa(5000001),syutugen(m,-1);
  syutugen[x]=0;
  a[0]=x;
  aruisekiwa[1]=x;
  ans+=a[0],n--;
  for(long i=1;n!=0;i++) {
    a[i]=a[i-1]*a[i-1]%m;
    aruisekiwa[i+1]=aruisekiwa[i]+a[i];
    if(syutugen[a[i]]==-1||aaa) {
      syutugen[a[i]]=i;
      ans+=a[i],n--;
    } else {
      aaa=true;
      ans+=n/(i-syutugen[a[i]])*(aruisekiwa[i]-aruisekiwa[syutugen[a[i]]]);
      ans+=(aruisekiwa[syutugen[a[i]]+n%(i-syutugen[a[i]])]-aruisekiwa[syutugen[a[i]]]);
      break;
    }
  }
  cout << ans << endl;
}