#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
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

struct {
	bool operator()( const pair<int,int>& a, const pair<int,int>& b ) {
		return ( a.second / (float)a.first )  < ( b.second / (float)b.first );
	}
} ratioCompXoverY;

struct {
	bool operator()( const pair<int,int>& a, const pair<int,int>& b ) {
		return ( a.first / (float)a.second )  < ( b.first / (float)b.second );
	}
} ratioCompYoverX;

void printAsteroids(map<pair<int,int>,int>& m, int height, int width, pair<int,int> station ) {

	//spacing
	for (int i=0; i<=70; i++)
		printf( "\n" );
	//cout << "---------------------------------" << endl;

	for (int i=0; i<=height; i++) {
		for (int j=0; j<width; j++) {
			//if ( m[station] ) printf( "%c", 178 );
			if ( i == station.first && j == station.second ) printf( "S");

			else if ( m[make_pair(i,j)] ) printf( "#" );
			else printf( " ");
		}
		printf( "\n" );
	}

	//pause
	usleep(50000);
}

pair<bool,pair<int,int>> destroyQuadrant( int init_x, int end_x, int init_y, int end_y, //all inclusive
										  pair<int,int> station,
										  map<pair<int,int>,int>*  m,
										  int* destroyed,
										  bool compXoverY ) {

		//get all positions of the quadrant
		vector<pair<int,int>> pos;
		for ( int dx = init_x; dx <= end_x; dx++ ) {
			//ps y can't equal station.y cause we do ( y-station.y )  / ( y-station.y )
			for ( int dy = init_y; dy <= end_y; dy++ ) {
				//insert all possible unique allowed combinations of cordinates on this quadrant
				pos.push_back( irrFrac( make_pair( dy, dx ) - station ) );
			}
		}


		//order
		if ( compXoverY ) {
			sort( pos.begin(), pos.end(), ratioCompXoverY );
			reverse( pos.begin(), pos.end() );
		}
		else
			sort( pos.begin(), pos.end(), ratioCompYoverX );


		//i said UNIQUE
		auto endIt = unique( pos.begin(), pos.end() );
		pos.erase( endIt, pos.end() );


		//loop over positions
		for ( auto stride=pos.begin(); stride!=pos.end(); ++stride ) {

			//walk in line until an asteroid is destroyed
			pair<int,int> destroyPos = station + *stride;

			//while ( inboundary( destroyPos, height, width ) ) {
			while ( inboundary( destroyPos, end_y, end_x ) ) {
				if ( (*m)[destroyPos] ) {
					(*m).erase( destroyPos );
					(*destroyed)++;
					if ( *destroyed >= 2000 ) return make_pair( true, destroyPos );
					printAsteroids( (*m), height, width, station );
					break;
				}

				destroyPos = destroyPos + *stride;
			}
		}

		return make_pair( false, make_pair( 0,0 ) );
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
	int destroyed = 0;
	pair<bool,pair<int,int>> ret;


	while ( true ) {

		//destroy 1st quadrant
		ret = destroyQuadrant( bcord.second, width, 0, bcord.first-1, bcord, &m, &destroyed, true );
		if ( ret.first ) break;
		// ...and the rest...
		ret = destroyQuadrant( bcord.second+1, width, bcord.first, height, bcord, &m, &destroyed, false );
		if ( ret.first ) break;
		ret = destroyQuadrant( 0, bcord.second, bcord.first+1, height, bcord, &m, &destroyed, true );
		if ( ret.first ) break;
		ret = destroyQuadrant( 0, bcord.second-1, 0, bcord.first, bcord, &m, &destroyed, false );
		if ( ret.first ) break;
	}

	cout << ret.second.second * 100 + ret.second.first << endl;
}
