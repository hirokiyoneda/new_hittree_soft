#include "DataProcess_lv1.hh"
#include "TSpline.h"

using namespace anl;

namespace hittree_gen 
{

DataProcess_lv1::DataProcess_lv1()
  : random_mode(1),
  readDetectorDatabase_(nullptr),
  eventDataBuffer_(nullptr)
{
}

ANLStatus DataProcess_lv1::mod_startup()
{
  register_parameter(&random_mode, "random_mode");
  return AS_OK;
}

ANLStatus DataProcess_lv1::mod_init()
{
  GetANLModule("ReadDetectorDatabase", &readDetectorDatabase_);
  GetANLModule("EventDataBuffer", &eventDataBuffer_);

  eventData_lv0 = eventDataBuffer_->getEventData_lv0();
  eventData_lv1 = eventDataBuffer_->getEventData_lv1();

  return AS_OK;
}

ANLStatus DataProcess_lv1::mod_ana()
{
//  eventData_lv0 = readEventTree_->getEventData();
  eventData_lv1->ResetData();

  int nsignal_lv1 = 0;
  for(int isignal = 0; isignal < eventData_lv0->get_nsignal(); ++isignal){
        int asicid = eventData_lv0->get_asicid(isignal);
        int asicch = eventData_lv0->get_asicch(isignal);
        int adc = eventData_lv0->get_adc(isignal);

        std::pair<int, int> p_asicid_and_asicch = std::make_pair(asicid, asicch);

        if(readDetectorDatabase_->isBlackch(p_asicid_and_asicch)){
            continue;
        }
        if(readDetectorDatabase_->isBadch(p_asicid_and_asicch)){
            continue;
        }

        int detid = readDetectorDatabase_->get_detid(p_asicid_and_asicch);
        eventData_lv1->set_detid(detid);
        int detch = readDetectorDatabase_->get_detch(p_asicid_and_asicch);
        eventData_lv1->set_detch(detch);
        int remapch = readDetectorDatabase_->get_remapch(p_asicid_and_asicch);
        eventData_lv1->set_remapch(remapch);
        int detector_material = readDetectorDatabase_->get_detector_material(p_asicid_and_asicch);
        eventData_lv1->set_detector_material(detector_material);
        int detector_HV = readDetectorDatabase_->get_detector_HV(p_asicid_and_asicch);
        eventData_lv1->set_detector_HV(detector_HV);
        double pos_x = readDetectorDatabase_->get_pos_x(p_asicid_and_asicch);
        eventData_lv1->set_pos_x(pos_x);
        double pos_y = readDetectorDatabase_->get_pos_y(p_asicid_and_asicch);
        eventData_lv1->set_pos_y(pos_y);
        double pos_z = readDetectorDatabase_->get_pos_z(p_asicid_and_asicch);
        eventData_lv1->set_pos_z(pos_z);
        double delta_x = readDetectorDatabase_->get_delta_x(p_asicid_and_asicch);
        eventData_lv1->set_delta_x(delta_x);
        double delta_y = readDetectorDatabase_->get_delta_y(p_asicid_and_asicch);
        eventData_lv1->set_delta_y(delta_y);
        double delta_z = readDetectorDatabase_->get_delta_z(p_asicid_and_asicch);
        eventData_lv1->set_delta_z(delta_z);

        double epi = getEPI(p_asicid_and_asicch, adc);
        eventData_lv1->set_epi(epi);

        ++nsignal_lv1;
  }
  eventData_lv1->set_nsignal(nsignal_lv1);

  return AS_OK;
}

double DataProcess_lv1::getEPI(std::pair<int, int> p_asicid_and_asicch, int adc){
    TSpline3 *calfunc = readDetectorDatabase_->get_calfunc(p_asicid_and_asicch);
    double epi = 0;
    if(random_mode == 0){
        epi = calfunc->Eval(adc);
    }else if(random_mode == 1){
        epi = calfunc->Eval(adc + random.Uniform(-0.5, 0.5) );
    }else if(random_mode == 2){
        epi = calfunc->Eval(adc + random.Uniform(0, 1) );
    }else if(random_mode == 3){
        epi = calfunc->Eval(adc + random.Uniform(-1, 0) );
    }
    return epi;
}

} /* namespace hittree_gen*/
