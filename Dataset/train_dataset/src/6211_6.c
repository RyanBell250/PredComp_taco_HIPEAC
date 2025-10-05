#include <bits/stdc++.h>

using namespace std;

typedef int real_int;

class IO {

public:

    int n;

    IO(int n) {

        this->n=n;

    }

    void print(string a,int newline=0) {

        printf("%s",a.c_str());

        if(newline==true) printf("\n");

    }



    void print(real_int a,int newline=0) {

        printf("%d",a);

        if(newline==true) printf("\n");

    }

    void print(char a,int newline=0) {

        printf("%c",a);

        if(newline==true) printf("\n");

    }


    void read(string &a) {

        char temp[n];

        scanf("%s",temp);

        a=temp;

        return ;

    }

    void read(char &a) {

        char b;

        scanf("%c",&b);

        a=b;

    }

    void read(real_int &a) {

        real_int b;

        scanf("%d",&b);

        a=b;

    }

};

vector<int> divisors(int n) {

    vector<int> res;

    for(int i=1; i*i<=n; i++) {

        int one=i;

        if(n%one==0) {

            res.push_back(one);

            if(one!=n/one)

                res.push_back(n/one);

        }

    }

    return res;

}

int power(int a,int b,int mod) {

    int res=1;

    while(b>0) {

        if(b&1)

            res=(res*a)%mod;

        a=(a*a)%mod;

        b>>=1;

    }

    return res;

}

bool isPrime(int n) {

    if (n == 1)return false;

    if (n == 2)return true;

    for (int i = 2; i * i <= n; i++)

        if (n % i == 0)return false;

    return true;

}

int fact(int n) {

    if(n==0)return 1;

    return (n*(fact(n-1)))%1000000007;

}

map<int, int> primeFactors(int n) {

    multiset<int> res;

    if (n == 1) {

        res.insert(1);

    }

    while (n % 2 == 0) {

        res.insert(2);

        n = n / 2;

    }

    for (int i = 3; i * i <= n; i += 2)while (n % i == 0) {

            res.insert(i);

            n = n / i;

        }

    if (n > 2)res.insert(n);

    map<int, int> req;

    for (int x : res) {

        req[x]++;

    }

    return req;

}

int dp[501][501][501];

int solve(vector<int> &a,int i,int last,int x) {

    if(i>=a.size()) {

        return 0;

    }

    if(dp[i][last+1][x]!=-1) {

        return dp[i][last+1][x];

    }

    int res=1e9;

    if(a[i]>x) {

        if(x>=last) {

            res=1+solve(a,i+1,x,a[i]);

        }

    }

    if(a[i]>=last)

        res=min(res,solve(a,i+1,a[i],x));

    dp[i][last+1][x] = res;

    return res;

}

auto main() -> decltype(14) {

    IO scanner(200005);

    int tt;

    scanner.read(tt);

    for(int _tt=1; _tt<=tt; _tt++) {

        int n;

        scanner.read(n);

        int x;

        scanner.read(x);

        for(int i = 0 ; !((i < (n+1))^1) ; i++) {

            for(int j = 0 ; j < 501 ; j++) {

                for(int k=0; k<501; k++) {

                    dp[i][k][j]=-1;

                }

            }

        }

        vector<int> a;

        for(int i = 0 ; !((i < (n))^1) ; i++) {

            int _temp;

            scanner.read(_temp);

            a.push_back(_temp);

        }

        int res=solve(a,0,-1,x);

        if(res==1e9) {

            res=-1;

        }

        scanner.print(res,1);

    }

    return 0;

}

