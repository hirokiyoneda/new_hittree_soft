#include "WriteHitTree_lv1.hh"

using namespace anl;

namespace hittree_gen{

WriteHitTree_lv1::WriteHitTree_lv1()
  : eventtree_(nullptr),
    hittree_lv1(nullptr),
    readEventTree_(nullptr),
    eventDataBuffer_(nullptr)
{
}

ANLStatus WriteHitTree_lv1::mod_init()
{
  GetANLModule("ReadEventTree", &readEventTree_);
  GetANLModule("EventDataBuffer", &eventDataBuffer_);
  
  eventData = eventDataBuffer_->getEventData_lv1();
  
  return AS_OK;
}

ANLStatus WriteHitTree_lv1::mod_his()
{
  eventtree_ = readEventTree_->getTreePointer();
  hittree_lv1 = eventtree_->CloneTree(0);

  hittree_lv1->SetNameTitle("hittree_lv1", "hittree_lv1");

  hittree_lv1->Branch("nsignal_lv1", &nsignal, "nsignal_lv1/I");
  hittree_lv1->Branch("detid_lv1", detid, "detid_lv1[nsignal_lv1]/I");
  hittree_lv1->Branch("detch_lv1", detch, "detch_lv1[nsignal_lv1]/I");
  hittree_lv1->Branch("remapch_lv1", remapch, "remapch_lv1[nsignal_lv1]/I");
  hittree_lv1->Branch("detector_material_lv1", detector_material, "detector_material_lv1[nsignal_lv1]/I");
  hittree_lv1->Branch("detector_HV_lv1", detector_HV, "detector_HV_lv1[nsignal_lv1]/I");
  hittree_lv1->Branch("epi_lv1", epi, "epi_lv1[nsignal_lv1]/D");
  hittree_lv1->Branch("pos_x_lv1", pos_x, "pos_x_lv1[nsignal_lv1]/D");
  hittree_lv1->Branch("pos_y_lv1", pos_y, "pos_y_lv1[nsignal_lv1]/D");
  hittree_lv1->Branch("pos_z_lv1", pos_z, "pos_z_lv1[nsignal_lv1]/D");
  hittree_lv1->Branch("delta_x_lv1", delta_x, "delta_x_lv1[nsignal_lv1]/D");
  hittree_lv1->Branch("delta_y_lv1", delta_y, "delta_y_lv1[nsignal_lv1]/D");
  hittree_lv1->Branch("delta_z_lv1", delta_z, "delta_z_lv1[nsignal_lv1]/D");

  return AS_OK;
}

ANLStatus WriteHitTree_lv1::mod_ana()
{
  nsignal = eventData->get_nsignal();
  for(int isignal = 0; isignal < nsignal; ++isignal){
      detid[isignal] = eventData->get_detid(isignal);
      detch[isignal] = eventData->get_detch(isignal);
      remapch[isignal] = eventData->get_remapch(isignal);
      detector_material[isignal] = eventData->get_detector_material(isignal);
      detector_HV[isignal] = eventData->get_detector_HV(isignal);
      epi[isignal] = eventData->get_epi(isignal);
      pos_x[isignal] = eventData->get_pos_x(isignal);
      pos_y[isignal] = eventData->get_pos_y(isignal);
      pos_z[isignal] = eventData->get_pos_z(isignal);
      delta_x[isignal] = eventData->get_delta_x(isignal);
      delta_y[isignal] = eventData->get_delta_y(isignal);
      delta_z[isignal] = eventData->get_delta_z(isignal);
  }

  hittree_lv1->Fill();

  return AS_OK;
}

} /* namespace hittree_gen*/
