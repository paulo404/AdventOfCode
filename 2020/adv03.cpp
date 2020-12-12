#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> forest;

unsigned long long solution1(unsigned int dx, unsigned int dy) {
  unsigned int x = 0, y = 0;

  int ouch = 0;
  int patt_len = forest[0].size();

  while ( (y+=dy) < forest.size() )
    if ( forest[y][(x+=dx)%patt_len] == '#' ) ouch++;

  return ouch;
}

unsigned long long solution2() {
  unsigned int slope[5][2] = {{1, 1},
                              {3, 1},
                              {5, 1},
                              {7, 1},
                              {1, 2}};

  unsigned long long oof = 1;
  for (int i = 0; i < 5; i++)
    oof *= solution1(slope[i][0], slope[i][1]);

  return oof;
}

int main() {
  std::string line;
  while ( getline(std::cin, line) ) forest.push_back(line);

  //std::cin << solution1() << std::endl;
  std::cout << solution2() << std::endl;

  return 0;
}
