#include <iostream>

#define LENGTH 6

using namespace std;

int crescent(string s) {
	for (int j = 0; j<LENGTH-1; j++) {
		if ( s[j] > s[j+1] )	return 0;
	}	
	return 1;
} 

int same(string s) {
	for (int k = 0; k<LENGTH-1; k++) {
		int start = k;
		while (s[k] == s[k+1]) {
			k++;	
		}
		if ( k - start == 1 ) return 1;
	}
	return 0;
	} 

int main(int argc, char** argv) {
	int min = atoi(argv[1]);
	int max = atoi(argv[2]);

	int count = 0;

	for (int i = min; i <= max; i++) {
		string s = to_string(i);
		//cout << s << endl;
		//cout << same(s) << crescent(s) << endl;
		if ( same(s) && crescent(s) )	count++;
	}
	string s = "111345";
	cout << same(s) << endl;
	cout << count << endl;
	return 0;
}
	
