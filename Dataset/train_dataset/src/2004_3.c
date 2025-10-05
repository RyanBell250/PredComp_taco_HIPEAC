#include <bits/stdc++.h>
#define MAXN 112345
using namespace std;

int n, cnt[MAXN];

int main(){
    scanf("%d", &n);
    for (int i=0;i<n;i++){
        int x;
        scanf("%d", &x);
        cnt[x]++;
        cnt[(x+1)]++;
        cnt[(x-1)]++;
    }
    sort(cnt, cnt+MAXN);
    printf("%d\n", cnt[MAXN-1]);
    return 0;
}
