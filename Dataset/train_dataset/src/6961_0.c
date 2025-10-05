#include <bits/stdc++.h>
typedef long long int ll;
using namespace std;
ll mod = 1e9+7;
#define MAXN   10000001
int spf[MAXN];
vector<int>ans(3e5,0);
int m;
void func(vector<tuple<int,char,int>>&v)
{   
	vector<tuple<int,char,int>>st;
	for(int i=0;i<v.size();i++)
	{
		if(st.size()==0)
		{
			st.push_back(v[i]);
		}
		else if(get<1>(st.back())=='R' && get<1>(v[i]) == 'L')
		{
			ans[get<2>(st.back())] = abs(get<0>(st.back()) - get<0>(v[i]))/2;
			ans[get<2>(v[i])] = abs(get<0>(st.back()) - get<0>(v[i]))/2;
			st.pop_back();
		}
		else{
			st.push_back(v[i]);
		}
	}
	vector<tuple<int,char,int>>vl;
	vector<tuple<int,char,int>>vr;
	for(int i=0;i<st.size();i++)
	{  
		if(get<1>(st[i])=='L')
		{
			vl.push_back(st[i]);
		}
		else{
			vr.push_back(st[i]);
		}
	}
	for(int i=1;i<vl.size();i=i+2)
	{
		ans[get<2>(vl[i])] = abs(get<0>(vl[i]) + get<0>(vl[i-1]))/2;
		ans[get<2>(vl[i-1])] = abs(get<0>(vl[i]) + get<0>(vl[i-1]))/2;
	}
	for(int i=vr.size()-1;i>0;i=i-2)
	{
		ans[get<2>(vr[i])] = abs(get<0>(vr[i]) - get<0>(vr[i-1]))/2  +  m - get<0>(vr[i]);
		ans[get<2>(vr[i-1])] = abs(get<0>(vr[i]) - get<0>(vr[i-1]))/2 + m - get<0>(vr[i]);
	}
	if(vl.size()%2 == 1 && vr.size()%2 == 1)
	{
		ans[get<2>(vr[0])] = (get<0>(vl[vl.size()-1]) - get<0>(vr[0]))/2  +  m ;
		ans[get<2>(vl[vl.size()-1])] = (get<0>(vl[vl.size()-1]) - get<0>(vr[0]))/2  +  m ;
	}
	else if(vl.size()%2)
	{
		ans[get<2>(vl[vl.size()-1])]=-1;
	}
	else if(vr.size()%2)
	{
		ans[get<2>(vr[0])]=-1;
	}
}
int main() 
{ 	
	int t;
	cin>>t;
	while(t--)
	{
		int n;
		cin>>n>>m;
		vector<tuple<int,char,int>>odd;
		vector<tuple<int,char,int>>even;
		vector<int>a;
		for(int i=0;i<n;i++)
		{
			int x;
			cin>>x;
			a.push_back(x);
		}
		for(int i=0;i<n;i++)
		{
			char c;
			cin>>c;
			tuple<int,char,int>p;
			get<0>(p) = a[i];
			get<1>(p) = c;
			get<2>(p) = i;
			if(a[i]%2)
			{
				odd.push_back(p);
			}
			else{
				even.push_back(p);
			}
		}
		sort(odd.begin(),odd.end());
		sort(even.begin(),even.end());
		func(odd);
		func(even);
		for(int i=0;i<n;i++)
		{
			cout<<ans[i]<<" ";
		}
		cout<<endl;
	}
} 
