#include <iostream>
using namespace std;

const int f = 1e5+7;
int a[f];
int main(){
	long long n,x;
	long long ans = 0;
	
	cin >> n >> x;
	for(int i = 0;i < n;i++){
		cin >> a[i];
	}
	for(int i = 0;i < n-1;i++){
		if(a[i]+a[i+1]>x){
			ans+=(a[i]+a[i+1]-x);
			if(a[i]<=x) a[i+1] = x-a[i];
			else a[i+1] = 0;
		}
	}
	cout << ans;
}