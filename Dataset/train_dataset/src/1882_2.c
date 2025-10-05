#include <iostream>
using namespace std;
int f(int n){
    if(n == 1) return 1;
    if(n == 2) return 2;
    if(n == 3) return 4;
    return f(n-1) + f(n-2) + f(n-3);
}
int main(void){
    while(true) {
        int n;
        cin >> n;
        if(n == 0) break;
        cout << ( f(n) / 3650 )+1 << endl;
    }
}
