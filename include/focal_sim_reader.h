#ifndef FOCAL_SIM_READER_H
#define FOCAL_SIM_READER_H

#include <string>
#include <memory.h>
#include <TTree.h>
#include <TFile.h>
#include <TParameter.h>
#include "definitions.h" // structs and hardcoded values


class FocalSimReader{
private:

  std::unique_ptr<TFile> in_tfile;
  std::unique_ptr<TFile> out_tfile;

  TTree *in_ttree;
  std::unique_ptr<TTree> out_ttree;

  std::string in_tfile_name;

  TFileFocalSim::EventPtr sim_event;
  TFileGeneric::EventPtr generic_event;


  // TTree raw pointer
  // TTree unique ptr

  bool infile_open();
  bool infile_close();
  bool outfile_open();
  bool outfile_close();
  std::string out_filename(); // Based on sim file
  int get_energy();
  void set_in_ttree_branches();
  void set_out_ttree_branches();
  void update_out_ttree_event();
  void clear_out_ttree_event();
  bool read_event(unsigned long entry);

public:

  FocalSimReader(std::string infile_name) : in_tfile_name(infile_name) {}
  bool to_generic_format();
};


#endif //FOCAL_SIM_READER_H
