#include <iostream>
#include "focal_sim_reader.h"
#include "superimpose_events.h"

int main(){

  /*
  FocalSimReader reader("../data/200_5_analysis.root");
  //FocalSimReader reader("../data/200_5_analysis_corner.root");
  reader.to_generic_format();
  */


  SuperimposeEvents evs("../data/adsf.root");
  std::cout << evs.get_file_count() << std::endl;
  evs.add_file("../data/converted/200_5_generic.root");
  evs.add_file("../data/converted/200_5_generic_corner.root");
  std::cout << evs.get_file_count() << std::endl;
  evs.convert();



  return 0;
}
