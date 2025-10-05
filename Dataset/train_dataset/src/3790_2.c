#include <bits/stdc++.h>
using namespace std;

const int INF = 1 << 28;

int num[100];
int in[100];
int out[100];
int Time[100];

int pos[100];

int res[100];

int main()
{
	for (int i = 0; i < 100; i++){
		num[i] = (i % 5 == 1) ? 5 : 2;
		in[i] = i * 5;
		out[i] = INF;
		Time[i] = 17 * (i % 2) + 3 * (i % 3) + 19;
 	}
	
	int seat = 0;
	int cnt = 0;
	int t = 0;
	queue<int> que;
	while (cnt < 100){
		for (int i = 0; i < 100; i++){
			if (out[i] == t){
				int x = (1 << num[i]) - 1;
				x <<= pos[i];
				seat -= x;
				cnt++;
				//printf("%d out %d\n", t, i);
			}
		}
		
		for (int i = 0; i < 100; i++){
			if (in[i] == t){
				que.push(i);
				//printf("%d in %d\n", t, i);
			}
		}
		
		while (que.size()){
			int p = que.front();
			bool f = false;
			for (int i = 0; i < 18 - num[p]; i++){
				int x = (1 << num[p]) - 1;
				x <<= i;
				if (seat & x) continue;
				seat += x;
				pos[p] = i;
				out[p] = t + Time[p];
				res[p] = t - in[p];
				que.pop();
				f = true;
				break;
			}
			if (!f) break;
		}
		t++;
	}
	
	int n;
	while (~scanf("%d", &n)){
		printf("%d\n", res[n]);
	}
}