#ifndef EventDataBuffer_H
#define EventDataBuffer_H 1

#include "BasicModule.hh"

#include "EventData_lv0.hh"
#include "EventData_lv1.hh"
#include "EventData_lv2.hh"
#include "EventData_lv3.hh"

class TFile;

namespace hittree_gen{

class EventDataBuffer: public anl::BasicModule
{
  DEFINE_ANL_MODULE(EventDataBuffer, 1.0);
public:
  EventDataBuffer() = default;
  ~EventDataBuffer() = default;

  anl::ANLStatus mod_startup();
  anl::ANLStatus mod_init();

  EventData_lv0* getEventData_lv0() const { return eventData_lv0; }
  EventData_lv1* getEventData_lv1() const { return eventData_lv1; }
  EventData_lv2* getEventData_lv2() const { return eventData_lv2; }
  EventData_lv3* getEventData_lv3() const { return eventData_lv3; }
  
private:
  EventData_lv0 *eventData_lv0;
  EventData_lv1 *eventData_lv1;
  EventData_lv2 *eventData_lv2;
  EventData_lv3 *eventData_lv3;
};

} /* namespace hittree_gen*/

#endif 
