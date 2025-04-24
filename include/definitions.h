#ifndef DEFINITIONS
#define DEFINITIONS

#include <string>
#include <vector>


namespace General{
  using float_type = double;
  using value_type = unsigned int;

  const std::string RootFileExtension = ".root";

}

namespace TFileFocalSim{
  const std::string TreeName = "T";
  const std::string EnergyName = "energy";

  // Under a TreeName
  const std::string x_branch = "x_pos";
  const std::string y_branch = "y_pos";
  const std::string value_branch = "value";
  const std::string label_branch = "particle";

  struct EventPtr{
    std::vector<General::float_type> *x = nullptr;
    std::vector<General::float_type> *y = nullptr;
    std::vector<unsigned int> *value = nullptr; // particular to focalsim, will prob normalize
  };
}


namespace TFileGeneric{
  const std::string TreeName = "EventsTree";
  const std::string TreeTitle = "Events Tree";
  const std::string EnergyName = "Energy";
  const std::string FileNameAppend = "_generic" + General::RootFileExtension;

  // Under a TreeName
  const std::string x_branch = "x";
  const std::string y_branch = "y";
  const std::string value_branch = "value";
  const std::string label_branch = "labels";
  const std::string label_idx_branch = "label_indices";
  const std::string fractions_branch = "fractions";
  const std::string energies_branch = "energies";
  const std::string clusters_branch = "clusters";
  const std::string cluster_idx_branch = "cluster_indices";

  struct EventPtr{
    std::vector<General::float_type> *x = nullptr;
    std::vector<General::float_type> *y = nullptr;
    std::vector<General::float_type> *value = nullptr;
    std::vector<General::float_type> *energies = nullptr;

    // Per cell flattened
    std::vector<unsigned int> *labels = nullptr; // Flattened
    std::vector<unsigned int> *label_idx = nullptr; // Index offsets
    std::vector<General::float_type> *fractions = nullptr; // Flattened

    std::vector<unsigned int> *clusters = nullptr;
    std::vector<unsigned int> *cluster_idx = nullptr;
  };
}


namespace Folders{
  const std::string DataFolder = "../data";
  const std::string ConvertedFolder = DataFolder + "/" + "converted";
}

#endif //DEFINITIONS
