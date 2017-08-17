#include "DataProcess_lv2_base.hh"

using namespace anl;

namespace hittree_gen 
{

DataProcess_lv2_base::DataProcess_lv2_base():
eventDataBuffer_(nullptr)
{
}

ANLStatus DataProcess_lv2_base::mod_startup()
{
  return AS_OK;
}

ANLStatus DataProcess_lv2_base::mod_init()
{
  GetANLModule("EventDataBuffer", &eventDataBuffer_);
  eventData_lv2 = eventDataBuffer_->getEventData_lv2();

  return AS_OK;
}

ANLStatus DataProcess_lv2_base::mod_ana()
{
  eventData_lv1 = eventDataBuffer_->getEventData_lv1();
  eventData_lv2->ResetData();

  doProcessing();

  return AS_OK;
}

} /* namespace hittree_gen*/
