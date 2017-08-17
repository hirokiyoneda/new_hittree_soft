#ifndef HitTreeGen_EventDataStruct_lv0_H
#define HitTreeGen_EventDataStruct_lv0_H 1

#include <string>
#include <vector>
#include "EventData.hh"

namespace hittree_gen{

class EventData_lv0 : public EventData{
    public:
        EventData_lv0() = default;
        ~EventData_lv0() = default;

        void ResetData(){
            nsignal = 0;
            asicid.clear();
            asicch.clear();
            adc.clear();

//            nhit.clear();
        }

        void set_nsignal(int _nsignal){ nsignal = _nsignal; }
        void set_asicid(int _asicid){ asicid.push_back(_asicid); }
        void set_asicch(int _asicch){ asicch.push_back(_asicch); }
        void set_adc(int _adc){ adc.push_back(_adc); }
//        void Set_nhit(int _nhit){ nhit.push_back(_nhit); }

        int get_nsignal() {return nsignal;}
        int get_asicid(int i) {return asicid[i];}
        int get_asicch(int i) {return asicch[i];}
        int get_adc(int i) {return adc[i];}
        //std::vector<int> Get_nhit() {return nhit;}

    private:
        int nsignal;
        std::vector<int> asicid;
        std::vector<int> asicch;
        std::vector<int> adc;
        //std::vector<int> nhit;
};

}

#endif
