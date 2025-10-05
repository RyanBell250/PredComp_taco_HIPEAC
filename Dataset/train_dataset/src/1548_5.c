#include <bits/stdc++.h>
using namespace std;

int main()
{
	int h, w, k;
	cin >> h >> w >> k;
	vector<string> ss(h);
	for (auto &&s : ss)
	{
		cin >> s;
	}

	int ans = (1 << 29);

	for (int S = 0; S < (1 << (h - 1)); S++)
	{
		int tmp = __builtin_popcount(S);

		vector<int> num(tmp + 1, 0);
		for (int j = 0; j < w; j++)
		{
			bool flag = false;
		back:;
			for (int i = 0, ind = 0; i < h; i++)
			{
				if (k < num[ind] + (ss[i][j] == '1'))
				{
					tmp++;
					for (auto &&x : num)
					{
						x = 0;
					}
					if (flag)
					{
						goto next;
					}
					flag = true;
					goto back;
				}

				num[ind] += (ss[i][j] == '1');

				if (S & (1 << i))
				{
					ind++;
				}
			}
		}

		ans = min(ans, tmp);

	next:;
	}

	cout << ans << endl;

	return 0;
}