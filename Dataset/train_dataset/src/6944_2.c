#include<iostream>
#include<map>
#include<string>
#include<queue>

int dir[4] = { -1, -4, 1, 4 };
std::map<std::string, int> res;

void bfs()
{
	std::queue<std::string> que;
	que.push( "01234567" );

	while( !que.empty() )
	{
		std::string p = que.front(); que.pop();

		int s;
		for( int i = 0; i != 8; ++i )
			if( p[i] == '0' )
				s = i;

		for( int i = 0; i != 4; ++i )
		{
			int ns = s + dir[i];

			if( ns < 0 || ns > 7 || ( s == 3 && i == 2 ) || ( s == 4 && !i ) )
				continue;

			std::string q = p;
			std::swap( q[s], q[ns] );

			if( !res[q] )
			{
				que.push( q );
				res[q] = res[p] + 1;
			}
		}
	}

	return;
}

int main()
{
	res["01234567"] = 1;

	bfs();

	while( true )
	{
		std::string s;

		for( int i = 0; i != 8; ++i )
		{
			int a;
			if( !( std::cin >> a ) )
				return 0;
			
			s += a + '0';
		}

		std::cout << res[s] - 1 << std::endl;
	}

	return 0;
}