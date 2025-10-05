#include <bits/stdc++.h>
using namespace std;

int main(int argc, char const *argv[])
{
	int a,b;
	cin>>a>>b;
	--a;--b;
	int h=100,w=100;
	char s[h][w];
	for (int i = 0; i < h; ++i)
	{
		for (int j = 0; j < w; ++j)
		{
			if (i<50)
			{
				s[i][j]='.';
			}
			else
			{
				s[i][j]='#';
			}
		}
	}
	int x=51,y=0;
	while (a>0)
	{
		s[x][y]='.';
		--a;
		if (y==98)
		{
			x+=2;y=0;
		}
		else
		{
			y+=2;
		}
	}
	x=0;y=0;
	while (b>0)
	{
		s[x][y]='#';
		--b;
		if (y==98)
		{
			x+=2;y=0;
		}
		else
		{
			y+=2;
		}
	}
	cout<<h<<" "<<w<<endl;
	for (int i = 0; i < h; ++i)
	{
		for (int j = 0; j < w; ++j)
		{
			cout<<s[i][j];
		}
		cout<<endl;
	}
	return 0;
}
