#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <climits>


// TODO trocar de mat pra  map
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
	while (getline(cin, s))  {
		stringstream ss(s);
		string dir;
		ss >> dir;
		cout << "in: " << s << endl;
		
		int i=0,j=0,rep=0;
		
        //cout << i << " " << j << " " << rep << " ";
        
		if (dir == "s")	break;

		if (dir == "D")	i=1; 
		if (dir == "U")	i=-1; 
		if (dir == "R")	j=1; 
		if (dir == "L")	j=-1; 

		ss >> rep;
		//cout << i << " " << j << " " << rep << endl;
		
		// draw line
		for (int k=0; k < rep; k++) {
		    cout << "k " << k << endl;
			m[cury+=i][curx+=j] = 1;
			cout << "m[" << cury << "][" << curx << "]" << endl;
		}
		    
	}
	cout << "1";
	
    // read 2nd line
	while (getline(cin, s))  {
		stringstream ss(s);
		string dir;
		cin >> dir;
		
		int i,j,rep = 0;

		if (dir == "s")	break;

		if (dir == "D")	i=1; 
		if (dir == "U")	i=-1; 
		if (dir == "R")	j=1; 
		if (dir == "L")	j=-1; 

		ss >> rep;
		
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
