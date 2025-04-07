#include "superimpose_events.h"


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
  }
}

void SuperimposeEvents::set_out_ttree_branches(){
  out_ttree->Branch(TFileGeneric::x_branch.c_str(), &out_event.x);
  out_ttree->Branch(TFileGeneric::y_branch.c_str(), &out_event.y);
  out_ttree->Branch(TFileGeneric::value_branch.c_str(), &out_event.value);
  out_ttree->Branch(TFileGeneric::label_branch.c_str(), &out_event.labels);
  out_ttree->Branch(TFileGeneric::label_idx_branch.c_str(), &out_event.label_idx);
  out_ttree->Branch(TFileGeneric::fractions_branch.c_str(), &out_event.fractions);
}


void SuperimposeEvents::clear_out_ttree_event(){
  out_event.x->clear();
  out_event.y->clear();
  out_event.value->clear();
  out_event.labels->clear();
  out_event.label_idx->clear();
  out_event.fractions->clear();
}


void SuperimposeEvents::superimpose(int idx_event){
  read_in_entries(idx_event);


  *out_event.x = *in_events.at(0).x;
  *out_event.y = *in_events.at(0).y;

  // Add a index 0 into the flatten index holder
  int label_idx_counter = 0;

  int channels = in_events.at(0).value->size();
  for (int i = 0; i < channels; i++){
    std::vector<General::float_type> values;
    //
    std::pair<General::float_type, std::vector<General::float_type>> ratios;
    for (int j = 0; j < get_file_count(); j++){
      values.push_back(in_events.at(j).value->at(i));
    }
    double sum = 0;
    for (auto &v : values) sum+=v;
    ratios = contributions(values);
    
    for (int j = 0; j < get_file_count(); j++){
      std::cout << in_events.at(j).value->at(i) << ",";
    }
    for (int j = 0; j < ratios.second.size(); j++){
      std::cout << ratios.second.at(j) << ",";
    }
    std::cout << std::endl;

    // Push_back value

    out_event.label_idx->push_back(label_idx_counter);
    out_event.value->push_back(ratios.first);
    for (int j = 0; j < get_file_count(); j++){
      out_event.labels->push_back(j+1);
      label_idx_counter++;
      out_event.fractions->push_back(ratios.second.at(j));
    }
    
  }

}

void SuperimposeEvents::convert(){
  // Assuming all have same length

  outfile_open();
  set_out_ttree_branches();



  int entries = in_ttrees.at(0)->GetEntries();
  set_in_ttrees_branches();

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
