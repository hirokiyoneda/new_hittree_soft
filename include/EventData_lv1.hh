#ifndef HitTreeGen_EventDataStruct_lv1_H
#define HitTreeGen_EventDataStruct_lv1_H 1

#include <string>
#include <vector>
#include "EventData.hh"

class TFile;

namespace hittree_gen{

class EventData_lv1 : public EventData{
    public:
        EventData_lv1() = default;
        ~EventData_lv1() = default;

        void ResetData(){
            nsignal = 0;
            detid.clear();
            detch.clear();
            remapch.clear();
            detector_material.clear();
            detector_HV.clear();
            pos_x.clear();
            pos_y.clear();
            pos_z.clear();
            delta_x.clear();
            delta_y.clear();
            delta_z.clear();
            epi.clear();
        };

        void set_nsignal(int _nsignal){ nsignal = _nsignal; };
        void set_detid(int _detid){ detid.push_back( _detid);};
        void set_detch(int _detch){ detch.push_back( _detch); };
        void set_remapch(int _remapch){ remapch.push_back( _remapch); };
        void set_detector_material(int _detector_material){ detector_material.push_back( _detector_material); };
        void set_detector_HV(int _detector_HV){ detector_HV.push_back( _detector_HV); };
        void set_pos_x(double _pos_x){ pos_x.push_back( _pos_x); };
        void set_pos_y(double _pos_y){ pos_y.push_back( _pos_y); };
        void set_pos_z(double _pos_z){ pos_z.push_back( _pos_z); };
        void set_delta_x(double _delta_x){ delta_x.push_back( _delta_x); };
        void set_delta_y(double _delta_y){ delta_y.push_back( _delta_y); };
        void set_delta_z(double _delta_z){ delta_z.push_back( _delta_z); };
        void set_epi(double _epi){ epi.push_back( _epi); };

        int get_nsignal(){ return nsignal;};
        int get_detid(int i){ return detid[i];};
        int get_detch(int i){ return detch[i];};
        int get_remapch(int i){ return remapch[i];};
        int get_detector_material(int i){ return detector_material[i];};
        int get_detector_HV(int i){ return detector_HV[i];};
        double get_pos_x(int i){ return pos_x[i];};
        double get_pos_y(int i){ return pos_y[i];};
        double get_pos_z(int i){ return pos_z[i];};
        double get_delta_x(int i){ return delta_x[i];};
        double get_delta_y(int i){ return delta_y[i];};
        double get_delta_z(int i){ return delta_z[i];};
        double get_epi(int i){ return epi[i];};

        void deleteSignal(int i){
            --nsignal;
            detid.erase(detid.begin() + i);
            detch.erase(detch.begin() + i);
            remapch.erase(remapch.begin() + i);
            detector_material.erase(detector_material.begin() + i);
            detector_HV.erase(detector_HV.begin() + i);
            pos_x.erase(pos_x.begin() + i);
            pos_y.erase(pos_y.begin() + i);
            pos_z.erase(pos_z.begin() + i);
            delta_x.erase(delta_x.begin() + i);
            delta_y.erase(delta_y.begin() + i);
            delta_z.erase(delta_z.begin() + i);
            epi.erase(epi.begin() + i);
        }

    private:

        int nsignal;
        std::vector<int> detid;
        std::vector<int> detch;
        std::vector<int> remapch;
        std::vector<int> detector_material;
        std::vector<int> detector_HV;
        std::vector<double> pos_x;
        std::vector<double> pos_y;
        std::vector<double> pos_z;
        std::vector<double> delta_x;
        std::vector<double> delta_y;
        std::vector<double> delta_z;
        std::vector<double> epi;
};

}

#endif
