#include "EventDataBuffer.hh"
#include <cstdio>
#include <iostream>

using namespace anl;

namespace hittree_gen
{

ANLStatus EventDataBuffer::mod_startup()
{
  return AS_OK;
}

ANLStatus EventDataBuffer::mod_init()
{
  eventData_lv0 = new EventData_lv0();
  eventData_lv1 = new EventData_lv1();
  eventData_lv2 = new EventData_lv2();
  eventData_lv3 = new EventData_lv3();
  return AS_OK;
}

} /* namespace hittree_gen*/
