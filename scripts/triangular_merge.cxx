#include <iostream>
#include "superimpose_events.h"

/*
 * Triangular merge (multiplication, amplification, upscaling, augmentation) of events in an N events file.
 * Let's say there are 5 events and I am merging 2, then it would be:
 *  1,2
 *  1,3
 *  1,4
 *  1,5
 *  2,3
 *  2,4
 *  2,5
 *  3,4
 *  3,5
 *  4,5
 *
 * It follows triangular numbers I believe. For N events you get ~ N^2/2 events.
 */


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
  evs.triangular_augmentation(std::stoi(argv[3]), std::stoi(argv[4]));

  return 0;
}
