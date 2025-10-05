#include<bits/stdc++.h>
using namespace std;
const long long MOD=1e9+7;
const int N=2e5+5;
int t;
long long x,y;
long long binS(){
	long long lo=1,hi=y,mid;
	while(lo<hi){
		mid=(lo+hi+1)/2;
		if(mid-1>x/(mid+1)) hi=mid-1;
		else lo=mid;
	}
	return lo;
}
long long binS2(long long val){
	long long lo=1,hi=y,mid;
	while(lo<hi){
		mid=(lo+hi+1)/2;
		if(x/(mid+1)<val) hi=mid-1;
		else lo=mid;
	}
	return lo;
}
int main(){
	scanf("%d", &t);
	while(t--){
		scanf("%lld %lld", &x, &y);
		long long ans=0,b=binS();
		ans=b*(b-1)/2;
		long long bc=x/(b+2);
		while(bc && binS2(bc+1)<y){
			ans+=bc*(max(binS2(bc),b)-max(binS2(bc+1),b));
			bc--;
		}
		printf("%lld\n", ans);
	}
	return 0;
}
