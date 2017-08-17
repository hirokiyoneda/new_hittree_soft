#ifndef HitTreeGen_DataProcess_lv1_H
#define HitTreeGen_DataProcess_lv1_H 1

#include "BasicModule.hh"
#include "ReadDetectorDatabase.hh"
#include "EventData_lv0.hh"
#include "EventData_lv1.hh"
#include "EventDataBuffer.hh"
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>
#include "TChain.h"
#include "TRandom3.h"

class TFile;

namespace hittree_gen{

class DataProcess_lv1: public anl::BasicModule
{
  DEFINE_ANL_MODULE(DataProcess_lv1, 1.0);
public:
  DataProcess_lv1();
  ~DataProcess_lv1() = default;

  anl::ANLStatus mod_startup();
  anl::ANLStatus mod_init();
  anl::ANLStatus mod_ana();

private:
  TRandom3 random;
  int random_mode;

  EventData_lv0 *eventData_lv0;
  EventData_lv1 *eventData_lv1;
  const ReadDetectorDatabase *readDetectorDatabase_;
  const EventDataBuffer *eventDataBuffer_;

  double getEPI(std::pair<int, int> p_asicid_and_asicch, int adc);
};

} /* namespace comptonsoft */

#endif 
