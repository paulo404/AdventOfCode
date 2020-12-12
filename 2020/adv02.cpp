#include <string>
#include <vector>
#include <iostream>
#include <sstream>

void solution1() {
  int valid_count = 0;

  std::string line;
  while ( getline(std::cin, line) ) {

    auto delim0 = line.find('-');
    auto delim1 = line.find(' ');
    auto delim2 = line.find(':');

    auto min = std::stoi(line.substr(0, delim0));
    auto max = std::stoi(line.substr(delim0+1, delim1));
    char req_char = line[delim2-1];
    auto passw = line.substr(delim2+2, line.size() );

    //std::cout << min << " " << max << " " << req_char << " " << passw << std::endl;

    int c_count = 0;
    for ( const auto& c : passw )
      if ( c == req_char ) c_count++;

    if ( c_count >= min && c_count <= max ) valid_count++;
  }

  std::cout << valid_count << std::endl;
}

void solution2() {
  int valid_count = 0;

  std::string line;
  while ( getline(std::cin, line) ) {

    auto delim0 = line.find('-');
    auto delim1 = line.find(' ');
    auto delim2 = line.find(':');

    auto pos0 = -1 + std::stoi(line.substr(0, delim0));
    auto pos1 = -1 + std::stoi(line.substr(delim0+1, delim1));
    char req_char = line[delim2-1];
    auto passw = line.substr(delim2+2, line.size() );

    std::cout << pos0 << " " << pos1 << " " << req_char << " " << passw << std::endl;

    if ( ( (passw[pos0] == req_char) + (passw[pos1] == req_char) ) == 1) valid_count++;
  }

  std::cout << valid_count << std::endl;
}
int main(int argc, char *argv[]) {
  //solution1();
  solution2();
  return 0;
}
