#include <iostream>
#include "superimpose_events.h"

int main(int argc, char* argv[]){

  if (argc != 5){
    std::cout << "Requires: 1) One input file; ";
    std::cout << "2) One output file; ";
    std::cout << "3) Number of particles. ";
    std::cout << "4) Max entries. " << std::endl;
    return 0;
  }

  SuperimposeEvents evs(argv[2]);
  evs.add_file(argv[1]);
  evs.random_merge(std::stoi(argv[3]), std::stoi(argv[4]));

  return 0;
}
