#ifndef HitTreeGen_DataProcess_lv2_merge_H
#define HitTreeGen_DataProcess_lv2_merge_H 1

#include "DataProcess_lv2_base.hh"

namespace hittree_gen{

class DataProcess_lv2_merge: public DataProcess_lv2_base
{
  DEFINE_ANL_MODULE(DataProcess_lv2_merge, 1.0);
public:
  DataProcess_lv2_merge();
  ~DataProcess_lv2_merge() = default;

  anl::ANLStatus mod_startup();

private:
  void initialize();
  void doProcessing();
  bool isAdjacent(int i);
  void merge();
  void set_merged_signal();
  void delete_signal();
  void extract_signal_over_threshold();
  void fill_signal_into_vector(int i);

  std::vector<int> filled_signal_index;

  double th_si_0V = 0;
  double th_si_HV = 0;
  double th_cdte_0V = 0;
  double th_cdte_HV = 0;

  int nsignal;
  int detid;
  int remapch;
  int detector_material;
  int detector_HV;

  std::vector<int> detch;
  std::vector<double> pos_x;
  std::vector<double> pos_y;
  std::vector<double> pos_z;
  std::vector<double> delta_x;
  std::vector<double> delta_y;
  std::vector<double> delta_z;
  std::vector<double> epi;

  int nsignal_lv2 = 0;
  int n_merged_signal = 0;
  double merged_pos_x;
  double merged_pos_y;
  double merged_pos_z;
  double merged_delta_x;
  double merged_delta_y;
  double merged_delta_z;
  double merged_epi;
};

} /* namespace comptonsoft */

#endif 
