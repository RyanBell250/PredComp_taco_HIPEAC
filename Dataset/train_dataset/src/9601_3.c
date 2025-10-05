#include <bits/stdc++.h>
using namespace std;

int main()
{
	int x,y,z,Y,N;
	cin>>N>>Y;
	
	for(x=0;x<=Y/10000;x++)
	   for(y=0;y<=Y/5000;y++)
	   {
	   	   z=N-x-y;
		   if(z>=0 && x*10000+y*5000+z*1000==Y)
		   {
		   	   cout<<x<<" "<<y<<" "<<z;
		   	   return 0;
		   }
	   }
	   
	cout<<"-1 -1 -1";
	return 0;
}