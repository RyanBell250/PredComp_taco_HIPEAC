#include <cstdio>
#include <iostream>
using namespace std;

int main()
{
	int n,y,a,b,c;
	cin>>n>>y;
	for(a=0;a<=y/10000;a++)
		for(b=0;b<=y/5000;b++)
		{
			c=n-a-b;
			if(c>=0 && a*10000+b*5000+c*1000==y)
			{
				cout<<a<<" "<<b<<" "<<c<<endl;
				return 0;
			}
		}
	cout<<"-1 -1 -1"<<endl;
	return 0;
}