#include <cstdio>
#include <cstring>
#include <algorithm>
#include <string>
#include <cmath>
#include <stack>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <list>
#include <iostream>
#include <sstream>
#include <climits>
#include <cfloat>
#include <complex>

using namespace std;

typedef long long ll;

ll encode(int* state)
{
	ll res = 0;
	for (int i = 0; i < 13; ++i)
		res = res << 4 | state[i];
	return res;
}
void decode(int* d, ll e)
{
	for (int i = 12; i >= 0; --i, e >>= 4)
		d[i] = e & 15;
}
void p(ll s)
{
	int d[13];
	decode(d, s);
	for (int i = 0; i < 13; ++i)
		printf("%d ", d[i]);
	printf("\n");
}

int main()
{
	map<ll, int> minSteps;
	int dir[] = { -1, 1, -2, 2, -4, 4 };
	map<int, bool> ok[3];

	int o[][9] = {
		{ 1, 2, 4, 5, 6, 7, 9, 10, -1 },
		{ 0, 10, -1 },
		{ 1, 2, 3, 5, 6, 7, -1 }
	};
	for (int i = 0; i < 3; ++i)
		for (int j = 0; o[i][j] != -1; ++j)
			ok[i][o[i][j]] = true;

	int initial[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 0 };
	ll t = encode(initial);
	minSteps[t] = 0;
	queue<ll> q;
	q.push(t);

	while (!q.empty())
	{
		ll e = q.front();
		q.pop();
		int d[13];
		decode(d, e);

		int zero_pos[2];
		for (int i = 0, j = 0; j < 2; ++i)
			if (!d[i])
				zero_pos[j++] = i;

		for (int i = 0; i < 2; ++i)
		{
			for (int j = 0; j < 6; ++j)
			{
				int a = zero_pos[i];
				int b = a + dir[j];
				if (a > b)
					swap(a, b);
				if (a < 0 || b > 12 || !d[a] && !d[b] || !ok[j/2][a])
					continue;

				int copy[13];
				memcpy(copy, d, sizeof(copy));
				swap(copy[a], copy[b]);
				ll next = encode(copy);

				if (!minSteps.count(next))
				{
					minSteps[next] = minSteps[e] + 1;
					if (minSteps[next] < 10)
						q.push(next);
				}
			}
		}
	}

	while (true)
	{
		int d[13];
		for (int i = 0; i < 13; ++i)
			scanf("%d", d + i);
		if (d[0] == -1)
			break;

		int ans = -1;
		ll s = encode(d);
		if (minSteps.count(s))
			ans = minSteps[s];
		else
		{
			map<ll, int> c;
			c[s] = 0;
			q = queue<ll>();
			q.push(s);
			while (!q.empty())
			{
				ll e = q.front();
				q.pop();
				int d[13];
				decode(d, e);

				int zero_pos[2];
				for (int i = 0, j = 0; j < 2; ++i)
					if (!d[i])
						zero_pos[j++] = i;

				for (int i = 0; i < 2; ++i)
				{
					for (int j = 0; j < 6; ++j)
					{
						int a = zero_pos[i];
						int b = a + dir[j];
						if (a > b)
							swap(a, b);
						if (a < 0 || b > 12 || !d[a] && !d[b] || !ok[j/2][a])
							continue;

						int copy[13];
						memcpy(copy, d, sizeof(copy));
						swap(copy[a], copy[b]);
						ll next = encode(copy);

						if (minSteps.count(next))
						{
							ans = 10 + c[e] + 1;
							goto End;
						}
						if (!c.count(next) && c[e] < 9)
						{
							c[next] = c[e] + 1;
							q.push(next);
						}
					}
				}
			}
		}
End:
		if (ans != -1)
			printf("%d\n", ans);
		else
			puts("NA");
	}

	return 0;
}