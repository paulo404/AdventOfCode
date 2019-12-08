#include <iostream>
#include <vector>
#include <climits>
#include <fstream>
#include <algorithm>

using namespace std;

#define HEIGHT 6
#define WIDTH 25

//problem with handling
int main() {
	int min0 = INT_MAX;
	int ans = 0;
//	int img[HEIGHT][WIDTH];
//	fill_n(img, HEIGHT*WIDTH, 2);		//initialize values 

	int val;
	while (!cin.eof()) {
		vector<int> count(10,0);
		for (int i=0; i<HEIGHT; i++)
			for (int j=0; j<WIDTH; j++) {
				cin >> val;
				count[val]++;
			}

		if (count[0] < min0) {
			min0 = count[0];
			ans = count[1] * count[2];
		}
	}

	cout << ans << endl;
	return 0;
}
