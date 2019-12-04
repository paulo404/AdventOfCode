#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <climits>
#include <map>

using namespace std;

int main() {
	map<pair<int,int>,int> m, n;
	vector<pair<int,int>> collision;

	// central port is at 1,1
	int curx=1, cury=1;

    // read first line
	string s; 
	int cost = 0;
	while (getline(cin, s))  {
		stringstream ss(s);
		string dir;
		ss >> dir;
		
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
		    pair<int,int> p = make_pair(cury+=i,curx+=j);
				cost++;
		    m[p] = m.count(p)? m[p] : cost;
		}
	}

	curx=1;
	cury=1;
	cost=0;
	
	while (getline(cin, s))  {
		stringstream ss(s);
		string dir;
		ss >> dir;
		
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
		    pair<int,int> p = make_pair(cury+=i,curx+=j);
				cost++;
		    n[p] = n.count(p)? n[p] : cost;
				if (m[p])
					collision.push_back(p);
		}
	}
	
	// find closest collsion
	int mindiff = INT_MAX;
 	for (auto p : collision) {
		int diff = m[p] + n[p];
		mindiff = diff < mindiff ? diff : mindiff;
 	}
	cout << mindiff << endl;

	return 0;
}
