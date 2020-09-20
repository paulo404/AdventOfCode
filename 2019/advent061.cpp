#include <iostream>
#include <map>
#include <sstream>

using namespace std;

#define Iter multimap<string,string>::iterator

multimap<string,string> t;

int  depthSum(string curr, int depth) {
	pair<Iter,Iter> range = t.equal_range(curr);
	int c = 0;	
	for(Iter it = range.first; it!=range.second; ++it) { // ++i??
		//cout << curr << ")" << it->second << ": " << depth << endl;
		c += depth + depthSum(it->second, depth+1);
	}
	return c;
}

//total of direct and indirect orbits in equivalent to summing the depth of each node on the tree
int main() {
	string parent, child, s;

	//populate tree
	while (getline(cin,s)) {
		stringstream ss(s);
		ss >> parent >> child;	
		t.insert(make_pair(parent,child));
		cout << parent << ")" << child << endl;
	}
	
	//calculate and sum depth (syntax only works on c++17)
	int total = depthSum("COM", 1);
	cout << total << endl;

	return 0;
}
