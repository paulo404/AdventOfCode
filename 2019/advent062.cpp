#include <iostream>
#include <map>
#include <unordered_map>
#include <sstream>

using namespace std;

#define Iter multimap<string,string>::iterator

multimap<string,string> t;

int depth(string curr, string goal, int d) {
	if (curr == goal) return d;
	pair<Iter,Iter> range = t.equal_range(curr);
	for(Iter it = range.first; it!=range.second; ++it) { // ++i??
		int res = depth(it->second, goal, d+1);
		if (res>=0) return res;
	}
	return -1;
}

//total of direct and indirect orbits in equivalent to summing the depth of each node on the tree
int main() {
	string parent, child, s;
	unordered_map<string,string> par;
	//populate tree
	while (getline(cin,s)) {
		stringstream ss(s);
		ss >> parent >> child;	
		t.insert(make_pair(parent,child));
		par[child] = parent;
		//cout << parent << ")" << child << endl;
	}

	string currpar = par["YOU"];
	string goal = par["SAN"];
	int dist = 0, res = 0;
	while(true) {
		res = depth(currpar, goal, 0);
		if(res >= 0) break;
		dist++;
		currpar = par[currpar];
	}
	dist += res;
	cout << dist << endl;
	
	return 0;
}
