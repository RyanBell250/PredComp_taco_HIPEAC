#include <cstdio>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <string>
#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <bitset>
#include <numeric>
#include <climits>
#include <cfloat>
using namespace std;
bool removePair(vector<int>& c, int x, int y)
{
    int n = c.size();
    if(x >= n || y >= n) 
        return false;
    if(c[x] != c[y]) 
        return false;
    c.erase(c.begin() + max(x,y));
    c.erase(c.begin() + min(x,y));
    return true;
}
map<vector<int>, int> memo;
int solve(const vector<int>& c)
{
    if(memo.find(c) != memo.end())
        return memo[c];
    int n = c.size();
    int ret = n;
    for(int i=0; i<n; ++i){
        vector<int> c2 = c;
        if(removePair(c2, i, i+4))
            ret = min(ret, solve(c2));
        if(i % 4 != 3){
            c2 = c;
            if(removePair(c2, i, i+1))
                ret = min(ret, solve(c2));
            c2 = c;
            if(removePair(c2, i, i+5))
                ret = min(ret, solve(c2));
        }
        if(i % 4 != 0){
            c2 = c;
            if(removePair(c2, i, i+3))
                ret = min(ret, solve(c2));
        }
    }
    return memo[c] = ret;
}
int main()
{
    int n;
    cin >> n;
    while(--n >= 0){
        vector<int> c(20);
        for(int i=0; i<20; ++i)
            cin >> c[i];
        memo.clear();
        cout << solve(c) << endl;
    }
    return 0;
}
