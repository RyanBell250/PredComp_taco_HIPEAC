#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) REP(i, 0, n)
#define ALL(v) v.begin(), v.end()
#define MSG(a) cout << #a << " " << a << endl;
#define REP(i, x, n) for (int i = x; i < n; i++)
#define OP(m) cout << m << endl;
typedef long long ll;
typedef unsigned long long ull;
int main()
{
    map<char, int> t;
    string s, s_trans;
    int n;
    char m[26];
    string suuti;
    cin >> n;
    getline(cin, s);
    rep(i, 26)
    {
        m[i] = char('a' + i);
        t[m[i]] = i;
    }
    rep(i, n)
    {
        bool flag = 0;
        getline(cin, s);
        s_trans = s;
        rep(a, 26)
        {
            rep(b, 26)
            {
                rep(k, s.size())
                {
                    if (s[k] == ' ')
                        s_trans[k] = ' ';
                    else
                        s_trans[k] = m[a * (t[s[k]] - b + 26) % 26];
                }
                if (s_trans.find("this") != string::npos || s_trans.find("that") != string::npos)
                {
                    flag = 1;
                    break;
                }
            }
            if (flag == 1)
                break;
        }
        OP(s_trans)
    }
    return 0;
}
