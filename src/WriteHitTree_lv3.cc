#include "WriteHitTree_lv3.hh"

using namespace anl;

namespace hittree_gen{

WriteHitTree_lv3::WriteHitTree_lv3()
  : hittree_lv2(nullptr),
    hittree_lv3(nullptr),
    readHitTree_lv2_(nullptr),
    eventDataBuffer_(nullptr)
{
}

ANLStatus WriteHitTree_lv3::mod_his()
{
  hittree_lv2= readHitTree_lv2_->getTreePointer();
  hittree_lv3 = hittree_lv2->CloneTree(0);

  hittree_lv3->SetNameTitle("hittree_lv3", "hittree_lv3");

  hittree_lv3->Branch("nhit", &nhit, "nhit/I");
  hittree_lv3->Branch("detid_lv3", detid, "detid_lv3[nhit]/I");
  hittree_lv3->Branch("detector_material_lv3", detector_material, "detector_material_lv3[nhit]/I");
  hittree_lv3->Branch("pos_x_lv3", pos_x, "pos_x_lv3[nhit]/D");
  hittree_lv3->Branch("pos_y_lv3", pos_y, "pos_y_lv3[nhit]/D");
  hittree_lv3->Branch("pos_z_lv3", pos_z, "pos_z_lv3[nhit]/D");
  hittree_lv3->Branch("delta_x_lv3", delta_x, "delta_x_lv3[nhit]/D");
  hittree_lv3->Branch("delta_y_lv3", delta_y, "delta_y_lv3[nhit]/D");
  hittree_lv3->Branch("delta_z_lv3", delta_z, "delta_z_lv3[nhit]/D");
  hittree_lv3->Branch("epi_lv3", epi, "epi_lv3[nhit]/D");

  return AS_OK;
}

ANLStatus WriteHitTree_lv3::mod_init()
{
  GetANLModule("ReadHitTree_lv2", &readHitTree_lv2_);
  GetANLModule("EventDataBuffer", &eventDataBuffer_);
  
  eventData = eventDataBuffer_->getEventData_lv3();
  
  return AS_OK;
}

ANLStatus WriteHitTree_lv3::mod_ana()
{
  nhit = eventData->get_nhit();
  for(int ihit = 0; ihit < nhit; ++ihit){
      detid[ihit] = eventData->get_detid(ihit);
      detector_material[ihit] = eventData->get_detector_material(ihit);
      pos_x[ihit] = eventData->get_pos_x(ihit);
      pos_y[ihit] = eventData->get_pos_y(ihit);
      pos_z[ihit] = eventData->get_pos_z(ihit);
      delta_x[ihit] = eventData->get_delta_x(ihit);
      delta_y[ihit] = eventData->get_delta_y(ihit);
      delta_z[ihit] = eventData->get_delta_z(ihit);
      epi[ihit] = eventData->get_epi(ihit);
  }

  hittree_lv3->Fill();

  return AS_OK;
}

} /* namespace hittree_gen*/
