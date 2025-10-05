// Problem: A. Add and Divide
// Contest: Codeforces - Codeforces Round #701 (Div. 2)
// URL: https://codeforces.com/problemset/problem/1485/A
// Memory Limit: 256 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
#define int long long int
#define fast_io ios_base::sync_with_stdio(false);cin.tie(NULL);
#define pb push_back 

int rec(int a,int b)
{
	if(a==0)
	return 0;
	
	if(b==10)
	return INT_MAX;
	
	int temp1=rec(a,b+1);
	int temp2=rec(a/b,b);
	
	if(temp2==INT_MAX&&temp2==INT_MAX)
	return INT_MAX;
	
	return 1+min(temp1,temp2);
 
}


int32_t main()
{
	fast_io
	int t;
	cin>>t;
	while(t--)
	{
		int a,b;
		cin>>a>>b;
		int ans=0;

		if(b==1)
		{
			b++;
			ans++;
		}
		if(b>=10)
		{
			while(a>0)
			{
				a/=b;
				ans++;
				
			}
			cout<<ans<<"\n";
			continue;
		}
		
		cout<<ans+rec(a,b)<<"\n";	
	}
	return 0;
}