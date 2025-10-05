#include "bits/stdc++.h"
#include<unordered_map>
#include<unordered_set>
#pragma warning(disable:4996)
using namespace std;
using ld = double;
const ld eps = 1e-9;

int adiv(int a) {
	map<int,int>mp;
	int num(a);
	for (int i = 2; i <= a; ++i) {
		while (num%i == 0) {
			mp[i]++;
			num/=i;
		}
	}
	int anum=0;
	for (auto m : mp) {
		anum-=m.first;
	}
	anum+=2*prev(mp.end())->first;
	return anum;
}

int main() {
	while (true) {

		int x,y;cin>>x>>y;
		if(!x)break;
		map<int,int>mp;
		vector<int>v(1e6+1,-1);
		int ans1=0,ans2=0;
		while (true) {
			x*=10;
			int a=x/y;
			int b=x%y;

			if (b == 0) {
				ans1++;
				break;
			}
			else {
				if (v[x/10]==-1) {
					v[x/10]=ans1;
					ans1++;
					x = b;
				}
				else {
					ans2=ans1-v[x/10];
					ans1=v[x/10];
					break;
				}
			}
		}
		cout<<ans1<<" "<<ans2<<endl;
	}
	return 0;
}
