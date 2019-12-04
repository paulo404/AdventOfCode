#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <climits>
#include <map>

using namespace std;

int main() {
	map<pair<int,int>,int> m;
	vector<pair<int,int>> collision;

	// central port is at 1,1
	int curx=1, cury=1;

    // read first line
	string s; 
	while (getline(cin, s))  {
		stringstream ss(s);
		string dir;
		ss >> dir;
		//cout << "in: " << s << endl;
		
		int i=0,j=0,rep=0;
		if (dir == "S")	break;

		if (dir == "D")	i=-1; 
		if (dir == "U")	i=1; 
		if (dir == "R")	j=1; 
		if (dir == "L")	j=-1; 

		ss >> rep;
		
		//check deu ruim
		if (i*j)    return 1;
		
		// draw line
		for (int k=0; k < rep; k++) {
		    m[make_pair(cury+=i,curx+=j)] = 1;
		    //cout << cury << " " << curx << " " << k << " " << endl;
		}
		    
	}
	//cout << "1";
	
	//back to central point
	curx=1, cury=1;
	cout << "-------------------------------------" << endl;
    // read 2nd line
	while (getline(cin, s))  {
		stringstream ss(s);
		string dir;
		ss >> dir;
		
		int i=0,j=0,rep=0;

		if (dir == "D")	i=-1; 
		if (dir == "U")	i=1; 
		if (dir == "R")	j=1; 
		if (dir == "L")	j=-1; 

		ss >> rep;
		
		//check deu ruim
		if (i*j)    return 1;
		
		// mark collisions
		for (int k=0; k < rep; k++) {
		    pair<int,int> p = make_pair(cury+=i,curx+=j);
		    if (m[p])	
			    collision.push_back(p);
		    //cout << cury << " " << curx << " " << k << " " << endl;
		}
			
	}
	
	// find closest collsion
	int mindiff = INT_MAX;
 	for (auto p : collision) {
		int diff = abs(p.first) + abs(p.second) - 2;
		cout << p.first << " " << p.second << endl;
		//cout << diff << endl;
		mindiff = diff < mindiff ? diff : mindiff;
 	}
	cout << mindiff << endl;

	return 0;
}
