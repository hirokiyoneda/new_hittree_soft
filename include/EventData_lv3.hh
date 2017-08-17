#ifndef HitTreeGen_EventDataStruct_lv3_H
#define HitTreeGen_EventDataStruct_lv3_H 1

#include <string>
#include <vector>

class TFile;

namespace hittree_gen{

class EventData_lv3 : public EventData{
    public:
        EventData_lv3() = default;
        ~EventData_lv3() = default;

        void ResetData(){
            nhit = 0;
            detid.clear();
            detector_material.clear();
            pos_x.clear();
            pos_y.clear();
            pos_z.clear();
            delta_x.clear();
            delta_y.clear();
            delta_z.clear();
            epi.clear();
        };

        void set_nhit(int _nhit){ nhit = _nhit; };
        void set_detid(int _detid){ detid.push_back( _detid);};
        void set_detector_material(int _detector_material){ detector_material.push_back( _detector_material); };
        void set_pos_x(double _pos_x){ pos_x.push_back( _pos_x); };
        void set_pos_y(double _pos_y){ pos_y.push_back( _pos_y); };
        void set_pos_z(double _pos_z){ pos_z.push_back( _pos_z); };
        void set_delta_x(double _delta_x){ delta_x.push_back( _delta_x); };
        void set_delta_y(double _delta_y){ delta_y.push_back( _delta_y); };
        void set_delta_z(double _delta_z){ delta_z.push_back( _delta_z); };
        void set_epi(double _epi){ epi.push_back( _epi); };

        int get_nhit(){ return nhit;};
        int get_detid(int i){ return detid[i];};
        int get_detector_material(int i){ return detector_material[i];};
        double get_pos_x(int i){ return pos_x[i];};
        double get_pos_y(int i){ return pos_y[i];};
        double get_pos_z(int i){ return pos_z[i];};
        double get_delta_x(int i){ return delta_x[i];};
        double get_delta_y(int i){ return delta_y[i];};
        double get_delta_z(int i){ return delta_z[i];};
        double get_epi(int i){ return epi[i];};

    private:

        int nhit;
        std::vector<int> detid;
        std::vector<int> detector_material;
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
