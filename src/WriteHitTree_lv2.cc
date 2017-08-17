#include "WriteHitTree_lv2.hh"

using namespace anl;

namespace hittree_gen{

WriteHitTree_lv2::WriteHitTree_lv2()
  : hittree_lv1(nullptr),
    hittree_lv2(nullptr),
    readHitTree_lv1_(nullptr),
    eventDataBuffer_(nullptr)
{
}

ANLStatus WriteHitTree_lv2::mod_his()
{

  GetANLModule("ReadHitTree_lv1", &readHitTree_lv1_);
  GetANLModule("EventDataBuffer", &eventDataBuffer_);
  
  hittree_lv1= readHitTree_lv1_->getTreePointer();
  hittree_lv2 = hittree_lv1->CloneTree(0);

  hittree_lv2->SetNameTitle("hittree_lv2", "hittree_lv2");

  hittree_lv2->Branch("nsignal_lv2", &nsignal, "nsignal_lv2/I");
  hittree_lv2->Branch("detid_lv2", detid, "detid_lv2[nsignal_lv2]/I");
  hittree_lv2->Branch("detector_material_lv2", detector_material, "detector_material_lv2[nsignal_lv2]/I");
  hittree_lv2->Branch("detector_HV_lv2", detector_HV, "detector_HV_lv2[nsignal_lv2]/I");
  hittree_lv2->Branch("n_merged_signal_lv2", n_merged_signal, "n_merged_signal_lv2[nsignal_lv2]/I");
  hittree_lv2->Branch("pos_x_lv2", pos_x, "pos_x_lv2[nsignal_lv2]/D");
  hittree_lv2->Branch("pos_y_lv2", pos_y, "pos_y_lv2[nsignal_lv2]/D");
  hittree_lv2->Branch("pos_z_lv2", pos_z, "pos_z_lv2[nsignal_lv2]/D");
  hittree_lv2->Branch("delta_x_lv2", delta_x, "delta_x_lv2[nsignal_lv2]/D");
  hittree_lv2->Branch("delta_y_lv2", delta_y, "delta_y_lv2[nsignal_lv2]/D");
  hittree_lv2->Branch("delta_z_lv2", delta_z, "delta_z_lv2[nsignal_lv2]/D");
  hittree_lv2->Branch("epi_lv2", epi, "epi_lv2[nsignal_lv2]/D");

  return AS_OK;
}

ANLStatus WriteHitTree_lv2::mod_init()
{
  
  return AS_OK;
}

ANLStatus WriteHitTree_lv2::mod_ana()
{
  eventData = eventDataBuffer_->getEventData_lv2();
  
  nsignal = eventData->get_nsignal();
  for(int isignal = 0; isignal < nsignal; ++isignal){
      detid[isignal] = eventData->get_detid(isignal);
      detector_material[isignal] = eventData->get_detector_material(isignal);
      detector_HV[isignal] = eventData->get_detector_HV(isignal);
      n_merged_signal[isignal] = eventData->get_n_merged_signal(isignal);
      pos_x[isignal] = eventData->get_pos_x(isignal);
      pos_y[isignal] = eventData->get_pos_y(isignal);
      pos_z[isignal] = eventData->get_pos_z(isignal);
      delta_x[isignal] = eventData->get_delta_x(isignal);
      delta_y[isignal] = eventData->get_delta_y(isignal);
      delta_z[isignal] = eventData->get_delta_z(isignal);
      epi[isignal] = eventData->get_epi(isignal);
  }

  hittree_lv2->Fill();

  return AS_OK;
}

} /* namespace hittree_gen*/
