#include <iostream>

using namespace std;

int main() {
	int sum = 0;
	int x ;

	while (cin >> x) {
		sum += x / 3 - 2;
	}

	cout << sum;

	return 0;
}