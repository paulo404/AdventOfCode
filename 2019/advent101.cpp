#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

template <typename T,typename U>
std::pair<T,U> operator-(const std::pair<T,U>& p) {
	return {-p.first,-p.second};
}

template <typename T,typename U>
std::pair<T,U> operator-(const std::pair<T,U>& l,const std::pair<T,U>& r) {
	return l+(-r);
}

template <typename T,typename U>
std::pair<T,U> operator+(const std::pair<T,U> & l,const std::pair<T,U> & r) {
	return {l.first+r.first,l.second+r.second};
}

inline int inboundary(pair<int,int> p, int height, int width) {
	//cout << "    y:0<=" << p.first << "<=" << height << "x:0<=" << p.second << "<=" << width << endl;
	return p.first>=0 && p.second>=0 && p.first<=height &&  p.second<=width;
}

inline int sgn(int val) { return (val>0)-(val<0); }

//finds irreducible fraction
pair<int,int> irrFrac(pair<int,int> p) {
	int n = p.first;
	int d = p.second;

	int red;
	while ( ( red = abs(__gcd(n,d)) ) > 1 ) {
		////cout << "n:" << n << " d:" << d << endl;
		n /= red;	
		d /= red;	
	}
	
	//remember to preserve sign
	return make_pair(n, d);
}

int main() {
	// read input
	map<pair<int,int>,int>  m;
	string line;
	int height=0, width=0;

	for (int i=0; getline(cin, line); i++)
		for (int j=0; j<line.length(); j++) {
			if (line[j] == '#' ) m[make_pair(i,j)]=1;
			height = max(height,i);
			width = max(width, j);
		}

	//cout << "finished reading" << endl;

	// find best viewing spot
	int best = 0;
	for (auto const& [a1, trash0] : m) {  //syntax is c++17 only
		map<pair<int,int>,int> am(m);
		am.erase(a1);
		//cout << "calculating for " << a1.first << " " << a1.second << endl;
		for (auto const& [a2, trash1] : am) {
			if (a1 == a2) continue;
			//find fraction
			pair<int,int> irrf = irrFrac(a2-a1);
			//cout << "  and : " << a2.first << " " << a2.second << ": frac" << irrf.first << " " << irrf.second << endl;
			//for all multiples of fraction
			for (pair<int,int> i=a2+irrf; inboundary(i,height, width); i= i+irrf) {
				//cout << "    erasing " << i.first << " " << i.second << endl;
				am.erase(i);
			}
		}

		//cout << "elem	" << am.size() << endl;
		best = am.size() > best ? am.size() : best;
	}

	cout << best << endl;
}
