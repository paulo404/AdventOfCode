#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <cmath>
#include <unistd.h>

using namespace std;

int height=0, width=0; //inclusive

template <typename T,typename U>
std::pair<T,U> operator-(const std::pair<T,U>& p) {
	return {-p.first,-p.second};
}

template <typename T,typename U>
std::pair<T,U> operator+(const std::pair<T,U> & l,const std::pair<T,U> & r) {
	return {l.first+r.first,l.second+r.second};
}

template <typename T,typename U>
std::pair<T,U> operator-(const std::pair<T,U>& l,const std::pair<T,U>& r) {
	return l+(-r);
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

float getAng( const pair<int,int>& p ) {
	return (p.first >= 0) * atan2(p.first, p.second) + (p.first < 0) * ( atan2(p.first, p.second) );
}

pair<int,int> rotate90( const pair<int,int>& p ) {
	return make_pair( p.second, p.first );
}

struct {
	bool operator()( const pair<int,int>& a, const pair<int,int>& b ) {
		return getAng( rotate90(a) ) > getAng( rotate90(b) );
	}
} angleComp;

void printAsteroids(map<pair<int,int>,int>& m, int height, int width, pair<int,int> station ) {

	//spacing
	for (int i=0; i<=70; i++)
		printf( "\n" );
	//cout << "---------------------------------" << endl;

	for (int i=0; i<=height; i++) {
		for (int j=0; j<width; j++) {
			if ( i == station.first && j == station.second ) printf( "S");
			else if ( m[make_pair(i,j)] ) printf( "*" );
			else printf( " ");
		}
		printf( "\n" );
	}

	//pause
	usleep(10000);
}

pair<int,int> destroy( pair<int,int> station, map<pair<int,int>,int>*  m, int numToDestroy ) {

		//get all positions
		vector<pair<int,int>> pos;
		for ( int x = 0; x <= width; x++ ) {
			for ( int y = 0; y <= height; y++ ) {
				if ( x == station.second && y == station.first ) continue;
				pos.push_back( irrFrac( make_pair( y, x ) - station ) );
			}
		}


		//order
		sort( pos.begin(), pos.end(), angleComp );

		//remove repeated pair
		auto endIt = unique( pos.begin(), pos.end() );
		pos.erase( endIt, pos.end() );

		int destroyed = 0;

		//loop over positions
		while (true) {

			for ( auto stride=pos.begin(); stride!=pos.end(); ++stride ) {

				//walk in line until an asteroid is destroyed
				pair<int,int> destroyPos = station + *stride;

				while ( inboundary( destroyPos, height, width ) ) {
					if ( (*m)[destroyPos] ) {
						(*m).erase( destroyPos );
						destroyed++;
						if ( destroyed >= numToDestroy ) return destroyPos;
						printAsteroids( (*m), height, width, station );
						break;
					}

					destroyPos = destroyPos + *stride;
				}
			}
		}

		return station;
}

int main() {
	// read input
	// y = first x = second
	map<pair<int,int>,int>  m;
	string line;

	for (int i=0; getline(cin, line); i++)
		for (int j=0; (unsigned long)j < line.length(); j++) {
			if (line[j] == '#' ) m[make_pair(i,j)] = 1;
			height = max(height,i);
			width = max(width, j);
		}

	//cout << "finished reading" << endl;

	// find best viewing spot
	unsigned int best = 0;
	pair<int,int> bcord;
	
	for (auto const& [a1, trash0] : m) {  //syntax is c++17 only
		map<pair<int,int>,int> am(m);
		am.erase(a1);

		for (auto const& [a2, trash1] : am) {
			if (a1 == a2) continue;
			//find fraction
			pair<int,int> irrf = irrFrac(a2-a1);
			//for all multiples of fraction
			for (pair<int,int> i=a2+irrf; inboundary(i,height, width); i= i+irrf) {
				am.erase(i);
			}
		}

		if (am.size() > best ) {
			best = am.size();
			bcord = a1;
		}
	}

	//destroy immediate asteroids clockwise order
	pair<int,int> lastDest = destroy( bcord, &m, 200000 );

	cout << lastDest.second * 100 + lastDest.first << endl;
}
