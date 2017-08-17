#ifndef HitTreeGen_EventData_H
#define HitTreeGen_EventData_H 1

#include <string>
#include <vector>

class TFile;

namespace hittree_gen{

class EventData{
public:
    EventData(){}
    ~EventData(){}

    virtual void ResetData() {}
};

}

#endif
