#include "DataProcess_lv3_base.hh"

using namespace anl;

namespace hittree_gen 
{

DataProcess_lv3_base::DataProcess_lv3_base():
eventDataBuffer_(nullptr)
{
}

ANLStatus DataProcess_lv3_base::mod_startup()
{
  return AS_OK;
}

ANLStatus DataProcess_lv3_base::mod_init()
{
  GetANLModule("EventDataBuffer", &eventDataBuffer_);
  eventData_lv2 = eventDataBuffer_->getEventData_lv2();
  eventData_lv3 = eventDataBuffer_->getEventData_lv3();

  return AS_OK;
}

ANLStatus DataProcess_lv3_base::mod_ana()
{
  eventData_lv3->ResetData();

  doProcessing();

  return AS_OK;
}

} /* namespace hittree_gen*/
