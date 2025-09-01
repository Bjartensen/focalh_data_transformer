#include "superimpose_events.h"
#include <random>
#include <set>


bool SuperimposeEvents::add_file(std::string in_filename){
  std::unique_ptr<TFile> new_tfile;
  new_tfile = std::make_unique<TFile>(in_filename.c_str(), "READ");
  if (new_tfile->IsZombie()) return false;

  new_tfile->cd();
  TTree *new_ttree = new_tfile->Get<TTree>(TFileGeneric::TreeName.c_str());
  if (!new_ttree) return false;

  in_tfiles.push_back(std::move(new_tfile));
  in_ttrees.push_back(new_ttree);
  in_events.emplace_back(); // Creates a new empty EventPtr in place

  return true;
}

bool SuperimposeEvents::outfile_open(){
  out_tfile = std::make_unique<TFile>(outfile_name.c_str(), "RECREATE");
  if (out_tfile->IsZombie()) return false;

  out_tfile->cd();
  out_ttree = std::make_unique<TTree>(TFileGeneric::TreeName.c_str(), TFileGeneric::TreeTitle.c_str());
  if (!out_ttree) return false;

  return true;
}


bool SuperimposeEvents::outfile_close(){
  out_tfile->cd();
  if (!out_tfile) return false;
  if (out_tfile->IsZombie()) return false;
  out_ttree.release();
  out_tfile->Close();
  return true;
}

bool SuperimposeEvents::infiles_close(){
  for (int i = 0; i < get_file_count(); i++){
    in_tfiles.at(i)->cd();
    if (!in_tfiles.at(i)) return false;
    if (in_ttrees.at(i)->IsZombie()) return false;
    in_tfiles.at(i)->Close();
  }
  return true;
}

void SuperimposeEvents::set_in_ttrees_branches(){
  for (int i = 0; i < in_ttrees.size(); i++){
    in_ttrees.at(i)->SetBranchAddress(TFileGeneric::x_branch.c_str(), &in_events.at(i).x);
    in_ttrees.at(i)->SetBranchAddress(TFileGeneric::y_branch.c_str(), &in_events.at(i).y);
    in_ttrees.at(i)->SetBranchAddress(TFileGeneric::value_branch.c_str(), &in_events.at(i).value);
    in_ttrees.at(i)->SetBranchAddress(TFileGeneric::label_branch.c_str(), &in_events.at(i).labels);
    in_ttrees.at(i)->SetBranchAddress(TFileGeneric::label_idx_branch.c_str(), &in_events.at(i).label_idx);
    in_ttrees.at(i)->SetBranchAddress(TFileGeneric::fractions_branch.c_str(), &in_events.at(i).fractions);
    in_ttrees.at(i)->SetBranchAddress(TFileGeneric::energies_branch.c_str(), &in_events.at(i).energies);
  }
}

void SuperimposeEvents::set_out_ttree_branches(){
  out_ttree->Branch(TFileGeneric::x_branch.c_str(), &out_event.x);
  out_ttree->Branch(TFileGeneric::y_branch.c_str(), &out_event.y);
  out_ttree->Branch(TFileGeneric::value_branch.c_str(), &out_event.value);
  out_ttree->Branch(TFileGeneric::label_branch.c_str(), &out_event.labels);
  out_ttree->Branch(TFileGeneric::label_idx_branch.c_str(), &out_event.label_idx);
  out_ttree->Branch(TFileGeneric::fractions_branch.c_str(), &out_event.fractions);
  out_ttree->Branch(TFileGeneric::energies_branch.c_str(), &out_event.energies);
}


void SuperimposeEvents::clear_out_ttree_event(){
  out_event.x->clear();
  out_event.y->clear();
  out_event.value->clear();
  out_event.labels->clear();
  out_event.label_idx->clear();
  out_event.fractions->clear();
  out_event.energies->clear();
}


void SuperimposeEvents::superimpose(int idx_event){
  read_in_entries(idx_event);

  // Same coordinates
  *out_event.x = *in_events.at(0).x;
  *out_event.y = *in_events.at(0).y;

  // Add a index 0 into the flatten index holder
  int label_idx_counter = 0;

  int channels = in_events.at(0).value->size();
  for (int i = 0; i < channels; i++){
    std::vector<General::float_type> values;
    std::pair<General::float_type, std::vector<General::float_type>> ratios;

    for (int j = 0; j < get_file_count(); j++){
      values.push_back(in_events.at(j).value->at(i));
    }
    ratios = contributions(values);

    out_event.label_idx->push_back(label_idx_counter);
    out_event.value->push_back(ratios.first);
    for (int j = 0; j < get_file_count(); j++){
      out_event.labels->push_back(j+1);
      label_idx_counter++;
      out_event.fractions->push_back(ratios.second.at(j));
    }
  }

  // Adding energies. Assuming single particle events of 1 energy.
  for (int j = 0; j < get_file_count(); j++){
    out_event.energies->push_back(in_events.at(j).energies->at(0));
  }
}

void SuperimposeEvents::convert(){
  // Assuming all have same length

  outfile_open();
  set_out_ttree_branches();

  set_in_ttrees_branches();
  int entries = in_ttrees.at(0)->GetEntries();

  for (int i = 0; i < entries; i++){
    superimpose(i);
    out_ttree->Fill();
    clear_out_ttree_event();
  }

  out_tfile->cd();
  out_tfile->Write();

  // loop over infiles and close
  if (!infiles_close()){
    std::cout << "Couldn't close all in files." << std::endl;
  }

  if (!outfile_close()){
    std::cout << "Couldn't close converted file." << std::endl;
  }
}


void SuperimposeEvents::read_in_entries(int idx){
  for (auto &v : in_ttrees) v->GetEntry(idx);
}


std::pair<General::float_type, std::vector<General::float_type>> SuperimposeEvents::contributions(
    std::vector<General::float_type> &values
    ){


  General::float_type sum = 0;
  std::vector<General::float_type> ratios (values.size(),0);
  for (const auto &v: values) sum += v;

  if (sum <= 0){
    return std::make_pair(sum, ratios);
  }

  for (int i = 0; i < values.size(); i++){
    ratios.at(i) = values.at(i)/sum;
  }

  return std::make_pair(sum, ratios);
}



// Bespoke function that combines events from a single file
void SuperimposeEvents::triangular_augmentation(int window, int max_events){

  if (in_tfiles.size() != 1){
    std::cout << "Expected only one input file." << std::endl;
    return;
  }


  outfile_open();
  set_out_ttree_branches();

  set_in_ttrees_branches();
  int entries = in_ttrees.at(0)->GetEntries();

  // Or do full permutation of n choose k, being aware of explosion and setting max
  // randomly generate without generating everything before? Random select of indices?
  
  std::vector<std::vector<int>> indices_vec;


  // What does this do?
  int count = 0;
  for (int i = 0; i < entries; i++){
    for (int j = i+1; j < entries; j++){
      count++;
      if (j+window - 1 > entries) break;
      if (count > max_events) break;
      std::vector<int> temp_vec;
      temp_vec.push_back(i);
      for (int k = j; k < j + window - 1; k++){
        // Moving window for more than 2 particles
        temp_vec.push_back(k);
      }
      indices_vec.push_back(temp_vec);
    }
  }


  for (int i = 0; i < indices_vec.size(); i++){
    if (i%1000 == 0){
      std::cout << "Mixing events ";
      for (const auto &v : indices_vec.at(i)){
        std::cout << v << ", ";
      }
      std::cout << " (event " << i << ")" << std::endl;
    }
    self_mix(indices_vec.at(i));
    out_ttree->Fill();
    clear_out_ttree_event();
  }

  out_tfile->cd();
  out_tfile->Write();

  // loop over infiles and close
  if (!infiles_close()){
    std::cout << "Couldn't close all in files." << std::endl;
  }

  if (!outfile_close()){
    std::cout << "Couldn't close converted file." << std::endl;
  }
}


std::set<int> random_tuple(int length, int low, int high){
  // Generate tuple of random number guaranteeing all are unique

  if (high-low < length-1){
    std::cout << "Cannot guarantee full unique list." << std::endl;
    std::set<int> null;
    return null;
  }

  // Random number engine
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(low, high);

  std::set<int> int_set;
  for (int k = 0; k < length; k++){
    int_set.insert(dis(gen));
  }

  while(int_set.size() < length){
    int r = dis(gen);
    int_set.insert(r);
  }
  return int_set;
}

void add_subset(std::set<int> &subset, std::set<std::set<int>> &superset){
  // Add a subset and warning if it failed
  if(!superset.insert(subset).second){   
    std::cout << "failed to insert ";
    for (const auto v : subset) std::cout << v << ",";
    if (superset.find(subset) != superset.end()){
      std::cout << " tuple already exists." << std::endl;
    }
  }
}

void SuperimposeEvents::random_merge(int window, int max_events){

  if (in_tfiles.size() != 1){
    std::cout << "Expected only one input file." << std::endl;
    return;
  }

  outfile_open();
  set_out_ttree_branches();

  set_in_ttrees_branches();
  int entries = in_ttrees.at(0)->GetEntries();

  std::vector<std::vector<int>> indices_vec;
  std::set<std::set<int>> superset;

  for (int i = 0; i < max_events; i++){
    std::set<int> int_set = random_tuple(window, 0, entries);
    add_subset(int_set, superset);
  }

  std::cout << "Superset length: " << superset.size() << std::endl;

  // Pad remaining
  int max_counter = 0;
  int max_its = 10*max_events;
  while(superset.size() < max_events){
    std::set<int> int_set = random_tuple(window, 0, entries);
    add_subset(int_set, superset);
    max_counter++;
    if (max_counter >= max_its){
      std::cout << "STOPPED PADDING EXTRA EVENTS, TRIED " << max_counter << " TIMES" << std::endl;
      break;
    }
  }
  std::cout << "Padded " << max_counter << " times." << std::endl;
  std::cout << "Superset length: " << superset.size() << std::endl;

  for (const auto s : superset){
    std::vector<int> subvector;
    for (const auto ss : s) subvector.push_back(ss);
    indices_vec.push_back(subvector);
  }

  // MAY STILL WANT TO RANDOMIZE SINCE THE SET ORDERS ITSELF
  // https://stackoverflow.com/questions/6926433/how-to-shuffle-a-stdvector#6926473


  // Keep the same
  for (int i = 0; i < indices_vec.size(); i++){
    if (i%1000 == 0){
      std::cout << "Mixing events ";
      for (const auto &v : indices_vec.at(i)){
        std::cout << v << ", ";
      }
      std::cout << " (event " << i << ")" << std::endl;
    }
    self_mix(indices_vec.at(i));
    out_ttree->Fill();
    clear_out_ttree_event();
  }

  out_tfile->cd();
  out_tfile->Write();

  // loop over infiles and close
  if (!infiles_close()){
    std::cout << "Couldn't close all in files." << std::endl;
  }

  if (!outfile_close()){
    std::cout << "Couldn't close converted file." << std::endl;
  }
}



void SuperimposeEvents::self_mix(std::vector<int> indices){

  int window = indices.size();

  // Construct containers
  // fill containers with GetEntry

  // To get coordinates
  read_in_entries(0);

  // Same coordinates
  *out_event.x = *in_events.at(0).x;
  *out_event.y = *in_events.at(0).y;
  int channels = in_events.at(0).value->size();



  // Across meaning they go across events, so not values
  // in ONE event but across events
  std::vector<std::vector<General::float_type>> values_across(
      channels, std::vector<General::float_type>(window,0)
  );
  std::vector<General::float_type> energies_across(window, 0);


  for (int i = 0; i < window; i++){
    in_ttrees.at(0)->GetEntry(indices.at(i));
    // TO-DO: Figure out when to use bounds checking and when not
    values_across[i] = *in_events.at(0).value;
    // Assuming single particle events with one energy
    out_event.energies->push_back(in_events.at(0).energies->at(0));
  }

  // Add a index 0 into the flatten index holder
  int label_idx_counter = 0;

  for (int i = 0; i < channels; i++){
    std::vector<General::float_type> values;
    std::pair<General::float_type, std::vector<General::float_type>> ratios;

    for (int j = 0; j < window; j++){
      values.push_back(values_across.at(j).at(i));
    }

    ratios = contributions(values);

    out_event.label_idx->push_back(label_idx_counter);
    out_event.value->push_back(ratios.first);
    for (int j = 0; j < window; j++){
      out_event.labels->push_back(j+1);
      label_idx_counter++;
      out_event.fractions->push_back(ratios.second.at(j));
    }

  }

  // Adding energies. Assuming single particle events of 1 energy.
  // Would rather just store all the energies
  /*
  std::cout << "Adding energies..." << std::endl;
  for (int j = 0; j < indices.size(); j++){
  //for (int j = 0; j < get_file_count(); j++){
    out_event.energies->push_back(in_events.at(j).energies->at(0));
  }
  */

}
