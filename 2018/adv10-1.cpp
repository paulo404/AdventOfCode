#include <stdio.h>
#include <vector>
#include <iostream>
#include <tuple>
#include <map>
#include <climits>

using namespace std;

#define MIN INT_MIN
#define MAX INT_MAX

/*
void show_points(set<tuple<int, int, int, int>> &points, int x_max, int y_max, int x_min, int y_min) {
    // todo: arruma eu
    for (auto [x1, y1, v1, v2] : points)
        cout << x1 << " " << y1 << " " << v1 << " " << v2 << endl; // vlw arthur <3
}
*/

int main() {
  // position=< 9,  1> velocity=< 0,  2>
  int x, y, vx, vy;
  vector<tuple<int,int,int,int>> points;
  while ( scanf("position=< %d, %d> velocity=< %d, %d> ", &x, &y, &vx, &vy) == 4 ) {
    points.push_back(make_tuple(x,y,vx,vy));
  }

  cout << points.size() << endl; // imprime 0 :(
  // show_points(points); // fixme!

  int t=0;
  while (true) {
    // simula
    map<pair<int, int>, int> atual;
    for ( auto [x, y, vx, vy] : points ) {
        atual[make_pair(x + vx*t, y + vy*t)] = 1;
    }

    // calcula retangulo de interesse
    int x_max = MIN, y_max = MIN, x_min = MAX, y_min = MAX;
    for ( auto [p, r] : atual ) {
        auto [x, y] = p;
        x_max = max(x, x_max);
        x_min = min(x, x_min);
        y_max = max(y, y_max);
        y_min = min(y, y_min);
    }

    //printação
    for ( int y = y_min; y <= y_max; y++ ) {
        for ( int x = x_min; x <= x_max; x++ ) {
            auto point = make_pair(x, y);
            if (atual[point]) {
                cout << "#";
            } else {
                cout << " ";
            }
        }
        cout << endl;
    }

    t++;

    //if ( !getchar() == 'c' )
        break;

  }


  // g++ -std=c++17 star.cpp && ./a.out < 1.in

}
