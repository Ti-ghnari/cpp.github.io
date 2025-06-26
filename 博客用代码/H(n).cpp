#include <iostream>
#define int long long
using namespace std;

int H(int n){
	int res = 0;
	for (int l = 1, r; l <= n; l = r + 1){
		int k = n / l;
		r = n / k;
		res += k * (r - l + 1);
	}
	return res;
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	int T;
	cin>>T;
	while (T--){
		int n;
		cin>>n;
		cout << H(n) << '\n';
	}
	return 0;
}
