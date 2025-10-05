#include <iostream>
#include <vector>

using namespace std;


int count(int w, int h) {
    int c = 0;
    if (w > 0 && h > 0 && (h % 2 == 0 or w % 2 == 0)){
        if (w % 2 == 0 && h % 2 != 0){
            c += count(w / 2, h);
            c += count(w / 2, h);
        }
        if (h % 2 == 0 && w % 2 != 0){
            c += count(w, h / 2);
            c += count(w, h / 2);
        }
        if (h % 2 == 0 && w % 2 == 0){
            c += count(max(h, w) / 2, min(h, w));
            c += count(max(h, w) / 2, min(h, w));
        }
    } else
        return 1;
    return c;
}

int main() {
    int t;
    cin >> t;
    for (int i = 0; i < t; ++i) {
        int w, h, n;
        cin >> w >> h >> n;
        if (count(w, h) >= n) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
    return 0;
}
