#include <iostream>
#include "focal_sim_reader.h"

int main(int argc, char* argv[]){

  if (argc != 3){
    std::cout << "Requires two arguments (in and out file), " << argc-1 << " given." << std::endl;
    return 0;
  }

  for (int i = 1; i < argc; i++){
    std::cout << argv[i] << std::endl;
  }

  FocalSimReader reader(argv[1], argv[2]);
  reader.to_generic_format();

  std::cout << "File converted." << std::endl;

  return 0;
}
