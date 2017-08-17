#ifndef HitTreeGen_WriteHitTree_lv1_H
#define HitTreeGen_WriteHitTree_lv1_H 1

#include "BasicModule.hh"
#include <memory>
#include "TTree.h"

#include "ReadEventTree.hh"
#include "EventDataBuffer.hh"
#include "EventData_lv1.hh"
#include "ConstantPar.hh"

namespace hittree_gen {

class WriteHitTree_lv1 : public anl::BasicModule
{
  DEFINE_ANL_MODULE(WriteHitTree_lv1, 1.0);
public:
  WriteHitTree_lv1();
  ~WriteHitTree_lv1() = default;
  
  anl::ANLStatus mod_init();
  anl::ANLStatus mod_his();
  anl::ANLStatus mod_ana();

private:
  const ReadEventTree *readEventTree_; 
  const EventDataBuffer *eventDataBuffer_;
  EventData_lv1 *eventData;
  TTree* eventtree_;
  TTree* hittree_lv1;

  int nsignal = 0;
  int detid[MAX_N_SIGNAL];
  int detch[MAX_N_SIGNAL];
  int remapch[MAX_N_SIGNAL];
  int detector_material[MAX_N_SIGNAL];
  int detector_HV[MAX_N_SIGNAL];
  double epi[MAX_N_SIGNAL];
  double pos_x[MAX_N_SIGNAL];
  double pos_y[MAX_N_SIGNAL];
  double pos_z[MAX_N_SIGNAL];
  double delta_x[MAX_N_SIGNAL];
  double delta_y[MAX_N_SIGNAL];
  double delta_z[MAX_N_SIGNAL];

};

} /* namespace oistapp */

#endif /* OISTAPP_OISTWriteHitTree_H */
