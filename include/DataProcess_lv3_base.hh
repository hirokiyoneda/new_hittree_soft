#ifndef HitTreeGen_DataProcess_lv3_base_H
#define HitTreeGen_DataProcess_lv3_base_H 1

#include "BasicModule.hh"
#include "EventDataBuffer.hh"
#include "EventData_lv2.hh"
#include "EventData_lv3.hh"
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>

class TFile;

namespace hittree_gen{

class DataProcess_lv3_base: public anl::BasicModule
{
  DEFINE_ANL_MODULE(DataProcess_lv3_base, 1.0);
public:
  DataProcess_lv3_base();
  ~DataProcess_lv3_base() = default;

  anl::ANLStatus mod_startup();
  anl::ANLStatus mod_init();
  anl::ANLStatus mod_ana();

protected:
  virtual void doProcessing() {};
  const EventDataBuffer *eventDataBuffer_;
  EventData_lv2 *eventData_lv2;
  EventData_lv3 *eventData_lv3;

private:
};

} /* namespace comptonsoft */

#endif 
