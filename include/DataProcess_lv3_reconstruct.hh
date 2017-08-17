#ifndef HitTreeGen_DataProcess_lv3_reconstruct_H
#define HitTreeGen_DataProcess_lv3_reconstruct_H 1

#include "DataProcess_lv3_base.hh"

namespace hittree_gen{

class DataProcess_lv3_reconstruct: public DataProcess_lv3_base
{
  DEFINE_ANL_MODULE(DataProcess_lv3_reconstruct, 1.0);
public:
  DataProcess_lv3_reconstruct();
  ~DataProcess_lv3_reconstruct() = default;

private:
  void initialize();
  void doProcessing();
  void reconstruct();
  void set_reconstructed_signal();
  void delete_signal();
  void fill_signal_into_vector(int i);

  std::vector<int> filled_signal_index;

  int detid;
  int detector_material;

  int nsignal;
  std::vector<double> pos_x_0V;
  std::vector<double> pos_y_0V;
  std::vector<double> pos_z_0V;
  std::vector<double> delta_x_0V;
  std::vector<double> delta_y_0V;
  std::vector<double> delta_z_0V;
  std::vector<double> epi_0V;

  std::vector<double> pos_x_HV;
  std::vector<double> pos_y_HV;
  std::vector<double> pos_z_HV;
  std::vector<double> delta_x_HV;
  std::vector<double> delta_y_HV;
  std::vector<double> delta_z_HV;
  std::vector<double> epi_HV;

  int nhit = 0;
  double reconstructed_pos_x;
  double reconstructed_pos_y;
  double reconstructed_pos_z;
  double reconstructed_delta_x;
  double reconstructed_delta_y;
  double reconstructed_delta_z;
  double reconstructed_epi;
};

} /* namespace comptonsoft */

#endif 
