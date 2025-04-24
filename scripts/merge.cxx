#include <iostream>
#include "superimpose_events.h"

int main(int argc, char* argv[]){


  if (argc <= 3){
    std::cout << "Requires at least two files [arg_1 to arg_n-1] and an out filename [arg_n]." << std::endl;
    return 0;
  }

  std::cout << "Attempting to merge files:" << std::endl;
  for (int i = 1; i < argc - 1; i++){
    std::cout << '\t' << argv[i] << std::endl;
  }

  SuperimposeEvents evs(argv[argc-1]);
  std::cout << evs.get_file_count() << std::endl;

  for (int i = 1; i < argc - 1; i++){
    evs.add_file(argv[i]);
  }

  std::cout << evs.get_file_count() << std::endl;
  evs.convert();


  std::cout << "File converted." << std::endl;
  

  return 0;
}
