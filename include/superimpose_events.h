/*
 * Superimpose events to fake multiparticle events in the generic format.
 * Assumes single-particle events.
 *
 * Author: Bjartur í Túni Mortensen
 */

#ifndef SUPERIMPOSE_EVENTS_H
#define SUPERIMPOSE_EVENTS_H

#include "definitions.h" // structs and hardcoded values
#include <iostream>
#include <string>
#include <memory.h>
#include <TTree.h>
#include <TFile.h>

class SuperimposeEvents{
private:
  std::unique_ptr<TFile> out_tfile;
  std::vector<std::unique_ptr<TFile>> in_tfiles;
  std::unique_ptr<TTree> out_ttree;
  std::vector<TTree*> in_ttrees;
  TFileGeneric::EventPtr out_event;
  std::vector<TFileGeneric::EventPtr> in_events;

  std::string outfile_name;


  //bool infile_open();
  bool infiles_close();
  bool outfile_open();
  bool outfile_close();

  // Convert files?
  // Set branches
  void set_in_ttrees_branches(); // For every ttree
  void set_out_ttree_branches();
  void clear_out_ttree_event();
  
  void superimpose(int idx_event);
  void read_in_entries(int idx);
  std::pair<General::float_type, std::vector<General::float_type>> contributions(
      std::vector<General::float_type> &values
      );

  void self_mix(std::vector<int> indices, int window);

public:

  // empty constructor?
  SuperimposeEvents(std::string filename):outfile_name(filename){;}
  // dd file to list
  // Add tfile -> calls and open function and adds to container
  bool add_file(std::string in_filename);
  // Check for length > 0 in in_tfiles
  int get_file_count(){return in_tfiles.size();}

  void convert();

  void triangular_augmentation(int window, int max_events);

};


#endif //SUPERIMPOSE_EVENTS_H

