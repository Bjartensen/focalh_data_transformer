#include "focal_sim_reader.h"

#include <iostream> // TO-DO: Remove


bool FocalSimReader::infile_open(){
  in_tfile = std::make_unique<TFile>(in_tfile_name.c_str(), "READ");
  if (in_tfile->IsZombie()) return false;
  in_tfile->cd();
  in_ttree = in_tfile->Get<TTree>(TFileFocalSim::TreeName.c_str());
  if (!in_ttree) return false;
  return true;
}

bool FocalSimReader::infile_close(){
  if (!in_tfile) return false;
  if (in_tfile->IsZombie()) return false;
  in_tfile->Close();
  return true;
}


bool FocalSimReader::outfile_open(){
  if (out_tfile_name.size() == 0) out_tfile_name = out_filename();
  out_tfile = std::make_unique<TFile>(out_tfile_name.c_str(), "RECREATE");
  if (out_tfile->IsZombie()) return false;

  out_tfile->cd();
  out_ttree = std::make_unique<TTree>(TFileGeneric::TreeName.c_str(), TFileGeneric::TreeTitle.c_str());
  if (!out_ttree) return false;

  return true;
}


bool FocalSimReader::outfile_close(){
  if (!out_tfile) return false;
  if (out_tfile->IsZombie()) return false;
  out_ttree.release();
  out_tfile->Close();
  return true;
}

std::string FocalSimReader::out_filename(){
  if (in_tfile->IsZombie()){
    std::cout << "Couldn't make header. File probably not open." << std::endl;
    return "";
  }
  if (!in_ttree){
    std::cout << "Couldn't make header. Tree not read." << std::endl;
    return "";
  }
  // Just get filename from CLI...
  std::string energy = std::to_string(get_energy());
  std::string entries = std::to_string(in_ttree->GetEntries());
  std::string filename = energy + "_" + entries + TFileGeneric::FileNameAppend;
  return Folders::ConvertedFolder + "/" + filename;
}

int FocalSimReader::get_energy(){
  return static_cast<TParameter<int>*>(in_tfile->Get(TFileFocalSim::EnergyName.c_str()))->GetVal();
}

void FocalSimReader::set_in_ttree_branches(){
  in_ttree->SetBranchAddress(TFileFocalSim::x_branch.c_str(), &sim_event.x);
  in_ttree->SetBranchAddress(TFileFocalSim::y_branch.c_str(), &sim_event.y);
  in_ttree->SetBranchAddress(TFileFocalSim::value_branch.c_str(), &sim_event.value);
}

void FocalSimReader::set_out_ttree_branches(){
  out_ttree->Branch(TFileGeneric::x_branch.c_str(), &generic_event.x);
  out_ttree->Branch(TFileGeneric::y_branch.c_str(), &generic_event.y);
  out_ttree->Branch(TFileGeneric::value_branch.c_str(), &generic_event.value);
  out_ttree->Branch(TFileGeneric::label_branch.c_str(), &generic_event.labels);
  out_ttree->Branch(TFileGeneric::label_idx_branch.c_str(), &generic_event.label_idx);
  out_ttree->Branch(TFileGeneric::fractions_branch.c_str(), &generic_event.fractions);
  out_ttree->Branch(TFileGeneric::energies_branch.c_str(), &generic_event.energies);
}

bool FocalSimReader::read_event(unsigned long entry){
  if (entry >= in_ttree->GetEntries()) return false;
  in_ttree->GetEntry(entry);
  return true;
}

void FocalSimReader::update_out_ttree_event(){
  // Converts the currently loaded branches
  *generic_event.x = *sim_event.x;
  *generic_event.y = *sim_event.y;
  *generic_event.value = std::vector<General::float_type>(sim_event.value->begin(), sim_event.value->end());
  
  // Need a flattened structure instead
  // vector of double, flattened values
  // vector of int, index offsets
  //*generic_event.label = std::vector<std::vector<General::float_type>>(generic_event.x->size(), std::vector<General::float_type>(1, 1.0f));

  std::vector<General::float_type> fractions;
  std::vector<unsigned int> labels;
  std::vector<unsigned int> labels_idx;
  std::vector<General::float_type> energies;
  energies.push_back(get_energy());
  for (int i = 0; i < generic_event.x->size(); i++){
    fractions.push_back(1);
    labels.push_back(1);
    labels_idx.push_back(i);
  }
  *generic_event.labels = labels;
  *generic_event.label_idx = labels_idx;
  *generic_event.fractions = fractions;
  *generic_event.energies = energies;
}

void FocalSimReader::clear_out_ttree_event(){
  generic_event.x->clear();
  generic_event.y->clear();
  generic_event.value->clear();
  generic_event.labels->clear();
  generic_event.label_idx->clear();
  generic_event.fractions->clear();
  generic_event.energies->clear();
}

bool FocalSimReader::to_generic_format(){
  std::cout << "Trying to convert file: " << in_tfile_name << std::endl;
  if (!infile_open()) return false;
  if (!outfile_open()) return false;

  int entries = in_ttree->GetEntries();

  set_in_ttree_branches();
  set_out_ttree_branches();

  for (int i = 0; i < entries; i++){
    if(!read_event(i)) break;
    update_out_ttree_event();

    out_tfile->cd();
    out_ttree->Fill();
    clear_out_ttree_event();
  }

  out_tfile->cd();
  out_ttree->Write();
  out_tfile->Write();
  if (!outfile_close()) return false;

  in_tfile->cd();
  if (!infile_close()) return false;

  return true;
}
