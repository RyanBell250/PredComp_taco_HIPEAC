#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
int main() {
	int A, B, X, w, ans = 0;
	cin >> A >> B >> X;
	if (A <= B) {
		while (X > 0) {
			ans += A;
			X -= 1000;
		}
	}
	else if (A >= B * 2) {
		while (X > 0) {
			ans += B;
			X -= 500;
		}
	}else{
		while (X > 500) {
			ans += A;
			X -= 1000;
		}
		while (X > 0) {
			ans += B;
			X -= 500;
		}
	}
	cout << ans << endl;
}
