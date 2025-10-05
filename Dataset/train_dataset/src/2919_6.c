 
    #include<iostream>
    using namespace std;
    const int N = 1000;
    int n, ans, now[N + 1];
    bool idax(int dep)
    {
        if(dep > ans)
            return false;
        if((now[dep] << (ans - dep)) < n) 
            return false;
        if(now[dep] == n)
            return true;
        for(int i=0; i<=dep; i++) {
            now[dep + 1] = now[dep] + now[i];
            if (idax(dep + 1))
                return true;
            now[dep + 1] = now[dep] - now[i];
            if (idax(dep + 1))
                return true;
        }
        return false;
    }
    int main()
    {
        now[0] = 1;
        while(cin>>n && n) {
            ans = 0;
            while(!idax(0))
                ans++;
            cout << ans << endl;
        }
        return 0;
    }
