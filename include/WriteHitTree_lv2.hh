#ifndef HitTreeGen_WriteHitTree_lv2_H
#define HitTreeGen_WriteHitTree_lv2_H 1

#include "BasicModule.hh"
#include <memory>
#include "TTree.h"

#include "ReadHitTree_lv1.hh"
#include "EventDataBuffer.hh"
#include "EventData_lv2.hh"
#include "ConstantPar.hh"

namespace hittree_gen {

class WriteHitTree_lv2 : public anl::BasicModule
{
  DEFINE_ANL_MODULE(WriteHitTree_lv2, 1.0);
public:
  WriteHitTree_lv2();
  ~WriteHitTree_lv2() = default;
  
  anl::ANLStatus mod_init();
  anl::ANLStatus mod_his();
  anl::ANLStatus mod_ana();

private:
  const ReadHitTree_lv1 *readHitTree_lv1_;
  const EventDataBuffer *eventDataBuffer_;
  EventData_lv2 *eventData;
  TTree* hittree_lv1;
  TTree* hittree_lv2;

  int nsignal = 0;
  int detid[MAX_N_SIGNAL];
  int detector_material[MAX_N_SIGNAL];
  int detector_HV[MAX_N_SIGNAL];
  int n_merged_signal[MAX_N_SIGNAL];
  double pos_x[MAX_N_SIGNAL];
  double pos_y[MAX_N_SIGNAL];
  double pos_z[MAX_N_SIGNAL];
  double delta_x[MAX_N_SIGNAL];
  double delta_y[MAX_N_SIGNAL];
  double delta_z[MAX_N_SIGNAL];
  double epi[MAX_N_SIGNAL];
};

} /* namespace oistapp */

#endif /* OISTAPP_OISTWriteHitTree_H */
