#include <iostream>
#include <algorithm>

typedef long long ll;
using namespace std;

int main(void) {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	int* a;
	int w[7] = { 1,2,5,10,20,50,100 };
	int n;
	int l, r;
	
	cin >> n;
	a = new int[n];
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	l = a[0];
	r = a[1];
	for (int i = 2; i < n; i++) {
		if (l <= r) {
			l += a[i];
			continue;
		}
		if (l > r) {
			r += a[i];
			continue;
		}
	}
	int count = 0;

	while (l != r) {
		for (int i = 6; i >= 0; i--) {
			if (l > r && l >= r + w[i]) {
				r += w[i];
				count++;
				
				break;
			}
			if (r > l && r >= l + w[i]) {
				l += w[i];
				count++;
				break;
			}
		}
	}
	cout << count;
	return 0;
}