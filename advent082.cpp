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
	int img[HEIGHT][WIDTH];
	fill_n(img[0], HEIGHT*WIDTH, 2);		//initialize values (takes an int*, and not an int**)

	int val;
	while (!cin.eof()) 
		for (int i=0; i<HEIGHT; i++)
			for (int j=0; j<WIDTH; j++) {
				cin >> val;
				if ( val != 2 && img[i][j] == 2 ) img[i][j] = val;
			}
	//print image
	for (int i=0; i<HEIGHT; i++) {
		for (int j=0; j<WIDTH; j++) {
			switch (img[i][j]) {
				case 0: cout << " "; break;
				case 1: cout << "X"; break;
				case 2: cout << " "; break;
			}
		}
		cout << endl;
	}
	return 0;
}
