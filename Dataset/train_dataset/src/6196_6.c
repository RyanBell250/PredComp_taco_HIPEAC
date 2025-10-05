// AOJ 0202
#include<algorithm>
#include<iostream>
#include<cstring>

bool isprime[1000001], dp[1000001];

void sieve()
{
	std::fill( isprime, isprime + 1000000, true );
	isprime[0] = isprime[1] = false;

	for( int i = 2; i <= 1000000; ++i )
		if( isprime[i] )
			for( int j = i * 2; j <= 1000000; j += i )
				isprime[j] = false;

	return;
}

int main()
{
	int n, x;

	sieve();

	while( std::cin >> n >> x, n | x )
	{
		memset( dp, false, sizeof( dp ) );
		dp[0] = true;

		int ans = 0;
		for( int i = 0; i != n; ++i )
		{
			int p;
			std::cin >> p;

			for( int j = p; j <= x; ++j )
			{
				if( dp[j-p] )
				{
					dp[j] = true;
					if( isprime[j] )
						ans = std::max( ans, j );
				}
			}
		}

		if( ans )
			std::cout << ans << std::endl;
		else
			std::cout << "NA" << std::endl;
	}

	return 0;
}