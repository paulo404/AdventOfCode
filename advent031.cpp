#include <iostream>
#include <vector>
#include <string>
#include <climits>

#define MAXHEIGHT 1000
#define MAXWIDTH 1000

using namespace std;

int main() {
	int m[MAXHEIGHT][MAXWIDTH];
	vector<pair<int,int>> collision;

	// central port is at 1,1
	int curx, cury = 1;

	// read first line
	string s; 
	while (true)  {
		cin >> s;
		string* f = s.split();
		int i,j,rep = 0;

		if (f[0] == "s")	break;

		if (f[0] == "D")	i=1; 
		if (f[0] == "U")	i=-1; 
		if (f[0] == "R")	j=1; 
		if (f[0] == "L")	j=-1; 

		f[1] >> rep;
		
		// draw line
		for (int k=0; k < rep; k++)
			m[cury+=i][curx+=j] = 1;
	}
// read 2nd line
	while (cin >> s)  {
		string[] f = s.split();
		int i,j,rep = 0;

		if (f[0] == "s")	break;

		if (f[0] == "D")	i=-1; 
		if (f[0] == "U")	i=1; 
		if (f[0] == "R")	j=1; 
		if (f[0] == "L")	j=-1; 

		f[1] >> rep;
		
		// mark collisions
		for (int k=0; k < rep; k++)
			if (m[cury+=i][curx+=j])	collision.push_back(make_pair(cury,curx));
	}
	
	// find closest collsion
	int mindiff = INT_MAX;
 	for (auto p : collision) {
		int diff = p.first - 1 + p.second - 1;
		mindiff = diff < mindiff ? diff : mindiff;
 	}
	cout << mindiff << endl;

	return 0;
}
