#include "DataProcess_lv2_merge.hh"

using namespace anl;

namespace hittree_gen 
{

DataProcess_lv2_merge::DataProcess_lv2_merge()
    :th_si_0V(0),
     th_si_HV(0),
     th_cdte_0V(0),
     th_cdte_HV(0)
{

}

ANLStatus DataProcess_lv2_merge::mod_startup()
{
  register_parameter(&th_si_0V, "Threshold_Si_0V");
  register_parameter(&th_si_HV, "Threshold_Si_HV");
  register_parameter(&th_cdte_0V, "Threshold_CdTe_0V");
  register_parameter(&th_cdte_HV, "Threshold_CdTe_HV");

  DataProcess_lv2_base::mod_startup();
}

void DataProcess_lv2_merge::doProcessing(){
    eventData_lv2->ResetData();
    nsignal_lv2 = 0;

    extract_signal_over_threshold();

    while(eventData_lv1->get_nsignal() != 0){
        initialize();

        nsignal = eventData_lv1->get_nsignal();

        for(int isignal = 0; isignal < nsignal; ++isignal){
            if(isignal == 0){
                fill_signal_into_vector(isignal);
            }else if(isAdjacent(isignal)){
                fill_signal_into_vector(isignal);
            }
        }
        merge();
        set_merged_signal();
        delete_signal();
    }
}

// Users should write this function !!! 
void DataProcess_lv2_merge::merge(){
    n_merged_signal = (int)detch.size();

    double max_epi = -1;
    int max_index = -1;
    for(auto itr = epi.begin(); itr != epi.end(); ++itr){
        merged_epi += *itr;
        if(*itr > max_epi){
            max_epi = *itr;
            max_index = itr - epi.begin();
        }
    }
    
    merged_pos_x = pos_x[max_index];
    merged_pos_y = pos_y[max_index];
    merged_pos_z = pos_z[max_index];

    merged_delta_x = delta_x[max_index];
    merged_delta_y = delta_y[max_index];
    merged_delta_z = delta_z[max_index];
}
// 

void DataProcess_lv2_merge::extract_signal_over_threshold(){
    int n = eventData_lv1->get_nsignal();
    for(int i = n-1; i >= 0; --i){
        
        int _detector_material = eventData_lv1->get_detector_material(i);
        int _detector_HV = eventData_lv1->get_detector_HV(i);
        double _epi = eventData_lv1->get_epi(i);

        if(_detector_material == 0){
            if(_detector_HV == 0){
                if(_epi < th_si_0V){
                    eventData_lv1->deleteSignal(i);
                }
            }else{
                if(_epi < th_si_HV){
                    eventData_lv1->deleteSignal(i);
                }
            }
        }else if(_detector_material == 1){
            if(_detector_HV == 0){
                if(_epi < th_cdte_0V){
                    eventData_lv1->deleteSignal(i);
                }
            }else{
                if(_epi < th_cdte_HV){
                    eventData_lv1->deleteSignal(i);
                }
            }
        }
    }

}

bool DataProcess_lv2_merge::isAdjacent(int i){
    if( detid ==  eventData_lv1->get_detid(i)
    &&  detector_material == eventData_lv1->get_detector_material(i)
    &&  detector_HV == eventData_lv1->get_detector_HV(i)
    ){
        int _detch = eventData_lv1->get_detch(i);
        for(auto itr = detch.begin(); itr != detch.end(); ++itr){
            if(*itr == _detch + 1 || *itr == _detch -1){
                return true;
            }
        }
        return false;
    }
    return false;
}

void DataProcess_lv2_merge::fill_signal_into_vector(int i){
    filled_signal_index.push_back(i);

    detch.push_back(eventData_lv1->get_detch(i));
    pos_x.push_back(eventData_lv1->get_pos_x(i));
    pos_y.push_back(eventData_lv1->get_pos_y(i));
    pos_z.push_back(eventData_lv1->get_pos_z(i));
    delta_x.push_back(eventData_lv1->get_delta_x(i));
    delta_y.push_back(eventData_lv1->get_delta_y(i));
    delta_z.push_back(eventData_lv1->get_delta_z(i));
    epi.push_back(eventData_lv1->get_epi(i));
}

void DataProcess_lv2_merge::initialize(){
    filled_signal_index.clear();

    detch.clear();

    pos_x.clear();
    pos_y.clear();
    pos_z.clear();

    delta_x.clear();
    delta_y.clear();
    delta_z.clear();

    epi.clear();

    merged_pos_x = 0;
    merged_pos_y = 0;
    merged_pos_z = 0;
    merged_delta_x = 0;
    merged_delta_y = 0;
    merged_delta_z = 0;
    merged_epi = 0;

    detid =  eventData_lv1->get_detid(0);
    remapch = eventData_lv1->get_remapch(0);
    detector_material = eventData_lv1->get_detector_material(0);
    detector_HV = eventData_lv1->get_detector_HV(0);
}

void DataProcess_lv2_merge::set_merged_signal(){
    nsignal_lv2++;

    eventData_lv2->set_nsignal(nsignal_lv2);
    eventData_lv2->set_detid(detid);
    eventData_lv2->set_detector_material(detector_material);
    eventData_lv2->set_detector_HV(detector_HV);
    eventData_lv2->set_n_merged_signal(n_merged_signal);
    eventData_lv2->set_pos_x(merged_pos_x);
    eventData_lv2->set_pos_y(merged_pos_y);
    eventData_lv2->set_pos_z(merged_pos_z);
    eventData_lv2->set_delta_x(merged_delta_x);
    eventData_lv2->set_delta_y(merged_delta_y);
    eventData_lv2->set_delta_z(merged_delta_z);
    eventData_lv2->set_epi(merged_epi);
}

void DataProcess_lv2_merge::delete_signal(){
    for(auto itr = filled_signal_index.rbegin(); itr != filled_signal_index.rend(); ++itr){
        eventData_lv1->deleteSignal(*itr);
    }
}

} /* namespace hittree_gen*/
