#ifndef HitTreeGen_DataProcess_lv2_base_H
#define HitTreeGen_DataProcess_lv2_base_H 1

#include "BasicModule.hh"
#include "EventDataBuffer.hh"
#include "EventData_lv1.hh"
#include "EventData_lv2.hh"
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>

class TFile;

namespace hittree_gen{

class DataProcess_lv2_base: public anl::BasicModule
{
  DEFINE_ANL_MODULE(DataProcess_lv2_base, 1.0);
public:
  DataProcess_lv2_base();
  ~DataProcess_lv2_base() = default;

  anl::ANLStatus mod_startup();
  anl::ANLStatus mod_init();
  anl::ANLStatus mod_ana();

protected:
  virtual void doProcessing() {};
  const EventDataBuffer *eventDataBuffer_;
  EventData_lv1 *eventData_lv1;
  EventData_lv2 *eventData_lv2;

private:
};

} /* namespace comptonsoft */

#endif 
