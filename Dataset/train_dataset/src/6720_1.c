#include <bits/stdc++.h>
#define rep(i,n) for(int i = 0; i < n; i++)
using namespace std;
typedef long long ll;
typedef pair<ll,ll> P;
typedef pair<ll,P> PP;
const long long int MOD = 1000000007;
const long long int INF = 1000000000;
ll x, y, k, al;
ll idsize;
map<ll,ll> toid;
vector<P> xy, yx;
ll ans = 0;
ll nod[200001];
ll bit[200001];
vector<ll> vec[200001];
ll forvec[200001];
ll sum(ll i){
	ll s = 0;
	while(i > 0){
		s = (s+bit[i]+MOD)%MOD;
		i -= i&-i;
	}
	return s;
}
void add(ll i, ll x){
	while(i <= idsize){
        bit[i] = (bit[i]+x+MOD)%MOD;
		i += i&-i;
	}
}
ll mod_pow(ll a, ll b){
    ll ret = 1;
    while(b){
        if(b&1) ret = ret*a%MOD;
        a = a*a%MOD;
        b /= 2;
    }
    return ret;
}
int main(){
    cin >> x >> y >> k;
    al = x*y%MOD;
    if(x*y-k <= 2){
        cout << 0 << endl;
        return 0;
    }
    rep(i,k){
        ll xx, yy;
        cin >> xx >> yy;
        xy.push_back(P(xx,yy));
        yx.push_back(P(yy,xx));
    }
    sort(xy.begin(),xy.end());
    sort(yx.begin(),yx.end());
    ans = (al-k+MOD)*(al-k-1+MOD)%MOD;
    ans = ans*(al-k-2+MOD)%MOD;
    ans = ans*mod_pow(6,MOD-2)%MOD;
    {
        ll cnt = 0;
        ll ad;
        ll ad2;
        rep(i,xy.size()){
            if(i == 0 || xy[i].first != xy[i-1].first){
                cnt++;
            }
            if(i == 0 || xy[i].first != xy[i-1].first){
                if(xy[i].second-1 > 0){
                    ad = ((xy[i].second)*(xy[i].second-1)/2)%MOD;
                    ad = ad*(al-k-xy[i].second+5*MOD)%MOD;
                    ans = (ans-ad+MOD)%MOD;
                }
                ad2 = xy[i].second*(xy[i].second-1)%MOD;
                ad2 = ad2*(xy[i].second-2)%MOD;
                ad2 = ad2*mod_pow(6,MOD-2)%MOD;
                ans = (ans-ad2+MOD)%MOD;
            } else{
                if(xy[i].second-xy[i-1].second-2 > 0){
                    ad = ((xy[i].second-xy[i-1].second-1)*(xy[i].second-xy[i-1].second-2)/2)%MOD;
                    ad = ad*(al-k-(xy[i].second-xy[i-1].second-1)+5*MOD)%MOD;
                    ans = (ans-ad+MOD)%MOD;
                }
                ad2 = (xy[i].second-xy[i-1].second-1)*(xy[i].second-xy[i-1].second-2)%MOD;
                ad2 = ad2*(xy[i].second-xy[i-1].second-3)%MOD;
                ad2 = ad2*mod_pow(6,MOD-2)%MOD;
                ans = (ans-ad2+MOD)%MOD;
            }
            if(i == xy.size()-1 || xy[i].first != xy[i+1].first){
                if(y-xy[i].second-2 > 0){
                    ad = ((y-xy[i].second-1)*(y-xy[i].second-2)/2)%MOD;
                    ad = ad*(al-k-(y-xy[i].second-1))%MOD;
                    ans = (ans-ad+MOD)%MOD;
                }
                ad2 = (y-xy[i].second-1)*(y-xy[i].second-2)%MOD;
                ad2 = ad2*(y-xy[i].second-3)%MOD;
                ad2 = ad2*mod_pow(6,MOD-2);
                ans = (ans-ad2+MOD)%MOD;
            }
        }
        ad = (y*(y-1)/2)%MOD;
        ad = ad*(x-cnt)%MOD;
        ad = ad*(al-k-y+5*MOD)%MOD;
        ans = (ans-ad+MOD)%MOD;
        ad2 = y*(y-1)%MOD;
        ad2 = ad2*(y-2)%MOD;
        ad2 = ad2*(x-cnt)%MOD;
        ad2 = ad2*mod_pow(6,MOD-2)%MOD;
        ans = (ans-ad2+MOD)%MOD;
        cnt = 0;
        rep(i,yx.size()){
            if(i == 0 || yx[i].first != yx[i-1].first){
                cnt++;
            }
            if(i == 0 || yx[i].first != yx[i-1].first){
                if(yx[i].second-1 > 0){
                    ad = (yx[i].second*(yx[i].second-1)/2)%MOD;
                    ad = ad*(al-k-yx[i].second+5*MOD)%MOD;
                    ans = (ans-ad+MOD)%MOD;
                }
                ad2 = yx[i].second*(yx[i].second-1)%MOD;
                ad2 = ad2*(yx[i].second-2)%MOD;
                ad2 = ad2*mod_pow(6,MOD-2)%MOD;
                ans = (ans-ad2+MOD)%MOD;
            } else{
                if(yx[i].second-yx[i-1].second-2 > 0){
                    ad = ((yx[i].second-yx[i-1].second-1)*(yx[i].second-yx[i-1].second-2)/2)%MOD;
                    ad = ad*(al-k-(yx[i].second-yx[i-1].second-1)+5*MOD)%MOD;
                    ans = (ans-ad+MOD)%MOD;
                }
                ad2 = (yx[i].second-yx[i-1].second-1)*(yx[i].second-yx[i-1].second-2)%MOD;
                ad2 = ad2*(yx[i].second-yx[i-1].second-3)%MOD;
                ad2 = ad2*mod_pow(6,MOD-2)%MOD;
                ans = (ans-ad2+MOD)%MOD;
            }
            if(i == yx.size()-1 || yx[i].first != yx[i+1].first){
                if(x-yx[i].second-2 > 0){
                    ad = ((x-yx[i].second-1)*(x-yx[i].second-2)/2)%MOD;
                    ad = ad*(al-k-(x-yx[i].second-1)+5*MOD)%MOD;
                    ans = (ans-ad+MOD)%MOD;
                }
                ad2 = (x-yx[i].second-1)*(x-yx[i].second-2)%MOD;
                ad2 = ad2*(x-yx[i].second-3)%MOD;
                ad2 = ad2*mod_pow(6,MOD-2)%MOD;
                ans = (ans-ad2+MOD)%MOD;
            }
        }
        ad = (x*(x-1)/2)%MOD;
        ad = ad*(y-cnt)%MOD;
        ad = ad*(al-k-x+2*MOD)%MOD;
        ans = (ans-ad+MOD)%MOD;
        ad2 = x*(x-1)%MOD;
        ad2 = ad2*(x-2)%MOD;
        ad2 = ad2*(y-cnt)%MOD;
        ad2 = ad2*mod_pow(6,MOD-2)%MOD;
        ans = (ans-ad2+MOD)%MOD;
    }
    {
        ll now = -1;
        ll last = -1;
        rep(i,xy.size()){
            if(xy[i].first > now+1){
                ll val = y*(xy[i].first-now-1)%MOD;
                nod[idsize] = val;
                idsize++;
            }
            if(xy[i].first == now){
                vec[idsize-1].push_back(xy[i].second-last-1);
                last = xy[i].second;
            } else{
                nod[idsize] = xy[i].second;
                toid[xy[i].first] = idsize;
                idsize++;
                last = xy[i].second;
            }
            if(i == xy.size()-1 || xy[i].first != xy[i+1].first){
                vec[idsize-1].push_back(y-last-1);
            }
            now = xy[i].first;
        }
        if(x > now+1){
            ll val = y*(x-now-1)%MOD;
            nod[idsize] = val;
            idsize++;
        }
    }
    rep(i,idsize){
        add(i+1,nod[i]);
    }
    {
        ll nowx = -1, nowy = -1;
        rep(i,yx.size()){
            ll id = toid[yx[i].second];
            if(yx[i].first > nowy+1){
                ll val = yx[i].first-nowy-1;
                val = val*(x-1)%MOD;
                val = val*(sum(idsize)-x+MOD)%MOD;
                ans = (ans+val)%MOD;
            }
            if(yx[i].first != nowy){
                ll val = yx[i].second-1;
                if(val > 0){
                    val = val*(sum(id)-yx[i].second+MOD)%MOD;
                    ans = (ans+val)%MOD;
                }
                nowy = yx[i].first;
                nowx = yx[i].second;
            } else{
                ll val = yx[i].second-nowx-2;
                if(val > 0){
                    val = val*(sum(id)-sum(toid[nowx]+1)-val-1+5*MOD)%MOD;
                    ans = (ans+val)%MOD;
                }
                nowx = yx[i].second;
            }
            if(i == yx.size()-1 || yx[i].first != yx[i+1].first){
                ll val = x-nowx-2;
                if(val > 0){
                    val = val*(sum(idsize)-sum(toid[nowx]+1)-val-1+5*MOD)%MOD;
                    ans = (ans+val)%MOD;
                }
            }
            ll q = vec[id][forvec[id]];
            forvec[id]++;
            ll dif = (q-nod[id]+MOD)%MOD;
            add(id+1,dif);
            nod[id] = q;
        }
        ll val = y-nowy-1;
        val = val*(x-1)%MOD;
        val = val*(sum(idsize)-x+MOD)%MOD;
        ans = (ans+val)%MOD;
    }
    cout << ans << endl;
}