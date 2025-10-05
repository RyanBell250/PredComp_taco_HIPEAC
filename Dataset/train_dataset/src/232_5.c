#include <iostream>
#include <algorithm>
using namespace std;
 
int main() {
	int a, b, c, d, e, na, nb, nc;
	while(cin >> a >> b >> c >> d >> e >> na >> nb >> nc, a){
		int ans = a * na + b * nb + c * nc;
 
		if(nc >= d){
			ans = min(ans, a * na + b * nb + e * nc);
		}
		else{
			ans = min(ans, a * na + b * nb + e * d);
 
			if(nb + nc >= d){
				int k = d - nc;
				ans = min(ans, a * na + b * (nb - k) + e * d);
			}
			else if(na + nb + nc >= d){
				int j = d - nb - nc;
				ans = min(ans, (na - j) * a + e * d);
			}
			else{
				ans = min(ans, e * d);
			}
		}
 
		cout << ans << endl;
	}
}