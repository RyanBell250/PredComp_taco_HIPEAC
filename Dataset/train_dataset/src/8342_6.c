/* * * * * * * * * * * * * * * * * * * * * * * * *\
*                                                 *
*                  VISHAL  GIRI                   *
*                                                 *
*      BIRLA INSTITUTE OF TECHNOLOGY , MERSA      *
*                                                 *
\* * * * * * * * * * * * * * * * * * * * * * * * */

#include<bits/stdc++.h>
#define ll long long int
#define deb(x) cout << #x << " = " << x << endl
#define deb2(x, y) cout << #x << " = " << x << "," << #y << " = " << y << endl
#define endl '\n'
using namespace std;

void solve()
{
   //start solving
   ll n,i=0,sum=0;
   string str="9";
   cin>>n; n--;
   if(n)
   {
       str+='8';
       n--;
   }
   while(n>=10)
    {
        n=n-10;
        str+="9012345678";
    }
   while(n--)
    {
        sum=abs((9+i))%10;
        i++;
        char a = sum + '0';
        str=str+a;
    }
    cout<<str<<endl;
}

int main()
{
    //ios_base::sync_with_stdio(false);cin.tie(NULL);
    int t; cin>>t; while(t--)
    {
        solve();
    }
    return 0;
}
