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

template <class T>
vector<vector<T> > matrixProduct(const vector<vector<T> >& x, const vector<vector<T> >& y)
{
    vector<vector<T> > z(2, vector<T>(2, 0));
    for(int i=0; i<2; ++i){
        for(int j=0; j<2; ++j){
            for(int k=0; k<2; ++k){
                z[i][j] += x[i][k] * y[k][j];
            }
        }
    }
    return z;
}

int n;

template <class T>
vector<T> transform(const vector<vector<T> >& x, const vector<T>& y)
{
    vector<T> z(2);
    z[0] = x[0][0] * y[0] + x[0][1] * y[1];
    z[1] = x[1][0] * y[0] + x[1][1] * y[1];
    if(z[0] < 0)
        z[0] = n + 1 + z[0];
    if(z[1] < 0)
        z[1] = n + 1 + z[1];
    return z;
}

int main()
{
    int q;
    long long a, b, c;
    int d, e, f, g;
    cin >> n >> q >> a >> b >> c >> d >> e >> f >> g;

    map<vector<int>, int> change;
    vector<vector<int> > p(2, vector<int>(2, 0));
    p[0][0] = p[1][1] = 1;
    vector<int> toY(n+1), toX(n+1);
    for(int i=1; i<=n; ++i)
        toY[i] = toX[i] = i;

    while(--q >= 0){
        string s;
        cin >> s;

        if(s == "WR"){
            vector<int> q(2);
            int v;
            cin >> q[0] >> q[1] >> v;
            q = transform(p, q);
            q[0] = toY[q[0]];
            q[1] = toX[q[1]];
            change[q] = v;
        }else if(s == "CP"){
            vector<int> q(2), r(2);
            cin >> q[0] >> q[1] >> r[0] >> r[1];
            q = transform(p, q);
            r = transform(p, r);
            q[0] = toY[q[0]];
            q[1] = toX[q[1]];
            r[0] = toY[r[0]];
            r[1] = toX[r[1]];
            if(change.find(q) == change.end())
                change[r] = (q[0] * a + q[1] * b) % c;
            else
                change[r] = change[q];
        }else if(s == "SR"){
            vector<int> q(2), r(2);
            cin >> q[0] >> r[0];
            q = transform(p, q);
            r = transform(p, r);
            swap(toY[q[0]], toY[r[0]]);
            swap(toX[q[1]], toX[r[1]]);
        }else if(s == "SC"){
            vector<int> q(2), r(2);
            cin >> q[1] >> r[1];
            q = transform(p, q);
            r = transform(p, r);
            swap(toY[q[0]], toY[r[0]]);
            swap(toX[q[1]], toX[r[1]]);
        }else if(s == "RL"){
            vector<vector<int> > q(2, vector<int>(2, 0));
            q[0][1] = 1;
            q[1][0] = -1;
            p = matrixProduct(p, q);
        }else if(s == "RR"){
            vector<vector<int> > q(2, vector<int>(2, 0));
            q[0][1] = -1;
            q[1][0] = 1;
            p = matrixProduct(p, q);
        }else if(s == "RH"){
            vector<vector<int> > q(2, vector<int>(2, 0));
            q[0][0] = -1;
            q[1][1] = 1;
            p = matrixProduct(p, q);
        }else if(s == "RV"){
            vector<vector<int> > q(2, vector<int>(2, 0));
            q[0][0] = 1;
            q[1][1] = -1;
            p = matrixProduct(p, q);

        }
    }

    long long h = 314159265;
    for(int y=d; y<=e; ++y){
        for(int x=f; x<=g; ++x){
            vector<int> q(2);
            q[0] = y;
            q[1] = x;
            q = transform(p, q);
            q[0] = toY[q[0]];
            q[1] = toX[q[1]];
            if(change.find(q) == change.end())
                h = (31 * h + ((q[0] * a + q[1] * b) % c)) % 1000000007;
            else
                h = (31 * h + change[q]) % 1000000007;
        }
    }
    cout << h << endl;

    return 0;
}