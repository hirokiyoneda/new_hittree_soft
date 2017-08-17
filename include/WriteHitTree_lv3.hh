#ifndef HitTreeGen_WriteHitTree_lv3_H
#define HitTreeGen_WriteHitTree_lv3_H 1

#include "BasicModule.hh"
#include <memory>
#include "TTree.h"

#include "ReadHitTree_lv2.hh"
#include "EventDataBuffer.hh"
#include "EventData_lv3.hh"
#include "ConstantPar.hh"

namespace hittree_gen {

class WriteHitTree_lv3 : public anl::BasicModule
{
  DEFINE_ANL_MODULE(WriteHitTree_lv3, 1.0);
public:
  WriteHitTree_lv3();
  ~WriteHitTree_lv3() = default;
  
  anl::ANLStatus mod_init();
  anl::ANLStatus mod_his();
  anl::ANLStatus mod_ana();

private:

  const ReadHitTree_lv2 *readHitTree_lv2_;
  const EventDataBuffer *eventDataBuffer_;
  EventData_lv3 *eventData;
  TTree* hittree_lv2;
  TTree* hittree_lv3;

  int nhit = 0;
  int detid[MAX_N_SIGNAL];
  int detector_material[MAX_N_SIGNAL];
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
