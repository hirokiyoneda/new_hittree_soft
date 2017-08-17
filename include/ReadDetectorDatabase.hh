#ifndef HitTreeGen_ReadDetectorDatabase_H
#define HitTreeGen_ReadDetectorDatabase_H 1

#include "BasicModule.hh"
#include "TTree.h"
#include "TFile.h"
#include "TSpline.h"
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

namespace hittree_gen{

class ReadDetectorDatabase: public anl::BasicModule
{
  DEFINE_ANL_MODULE(ReadDetectorDatabase, 1.0);
public:
  ReadDetectorDatabase();
  ~ReadDetectorDatabase() = default;
  
  anl::ANLStatus mod_startup();
  anl::ANLStatus mod_init();

  int get_nasic() const {return nasic;}
  int get_asicid(int iasic) const {return vec_asicid[iasic];}

  int get_detid(std::pair<int, int> p_asicid_and_asicch) const {
      std::pair<int, int> p_detid_and_detch = map_detid_and_detch[p_asicid_and_asicch];
      return p_detid_and_detch.first;
  }
  int get_detch(std::pair<int, int> p_asicid_and_asicch) const {
      std::pair<int, int> p_detid_and_detch = map_detid_and_detch[p_asicid_and_asicch];
      return p_detid_and_detch.second;
  }
  int get_remapch(std::pair<int, int> p_asicid_and_asicch) const {
      return map_remapch[p_asicid_and_asicch];
  }
  int get_detector_material(std::pair<int, int> p_asicid_and_asicch) const {
      std::pair<int, int> p_detid_and_detch = map_detid_and_detch[p_asicid_and_asicch];
      return map_detector_material[p_detid_and_detch];
  }
  int get_detector_HV(std::pair<int, int> p_asicid_and_asicch) const {
      std::pair<int, int> p_detid_and_detch = map_detid_and_detch[p_asicid_and_asicch];
      return map_detector_HV[p_detid_and_detch];
  }
  double get_pos_x(std::pair<int, int> p_asicid_and_asicch) const {
      std::pair<int, int> p_detid_and_detch = map_detid_and_detch[p_asicid_and_asicch];
      return map_pos_x[p_detid_and_detch];
  }
  double get_pos_y(std::pair<int, int> p_asicid_and_asicch) const {
      std::pair<int, int> p_detid_and_detch = map_detid_and_detch[p_asicid_and_asicch];
      return map_pos_y[p_detid_and_detch];
  }
  double get_pos_z(std::pair<int, int> p_asicid_and_asicch) const {
      std::pair<int, int> p_detid_and_detch = map_detid_and_detch[p_asicid_and_asicch];
      return map_pos_z[p_detid_and_detch];
  }
  double get_delta_x(std::pair<int, int> p_asicid_and_asicch) const {
      std::pair<int, int> p_detid_and_detch = map_detid_and_detch[p_asicid_and_asicch];
      return map_delta_x[p_detid_and_detch];
  }
  double get_delta_y(std::pair<int, int> p_asicid_and_asicch) const {
      std::pair<int, int> p_detid_and_detch = map_detid_and_detch[p_asicid_and_asicch];
      return map_delta_y[p_detid_and_detch];
  }
  double get_delta_z(std::pair<int, int> p_asicid_and_asicch) const {
      std::pair<int, int> p_detid_and_detch = map_detid_and_detch[p_asicid_and_asicch];
      return map_delta_z[p_detid_and_detch];
  }

  bool isBlackch(std::pair<int, int> p_asicid_and_asicch) const {
      if(get_remapch(p_asicid_and_asicch) < 0){
        return true;
      }
      return false;
  }
  bool isBadch(std::pair<int, int> p_asicid_and_asicch) const {
      std::pair<int, int> p_detid_and_detch = map_detid_and_detch[p_asicid_and_asicch];
      int badch = map_badch[p_detid_and_detch];
      if(badch == 1){
        return true;
      }
      return false;
  }
  TSpline3* get_calfunc(std::pair<int, int> p_asicid_and_asicch) const {
      return map_calfunc[p_asicid_and_asicch];
  }

private:
  void load_Map_Databese();
  void load_Profile_Databese();
  void load_Calfunc_Databese();

  int nasic;

  std::string map_Filename;
  std::string profile_Filename;
  std::string calfunc_Filename;

  TFile *map_File;
  TFile *profile_File;
  TFile *calfunc_File;

  TTree *detector_map;
  TTree *detector_profile;

  Int_t asicid;
  Int_t asicch;
  Int_t remapch;

  Int_t detid;
  Int_t detch;

  Int_t detector_material;
  Int_t detector_HV ;
  Double_t pos_x ;
  Double_t pos_y ;
  Double_t pos_z ;
  Double_t delta_x ;
  Double_t delta_y ;
  Double_t delta_z ;
  Int_t badch;

  //asicid_and_asicch -> 
  mutable std::vector<int> vec_asicid;
  mutable std::vector< std::pair<int, int> > vec_asicid_and_asicch;

  mutable std::map<std::pair<int, int>, int> map_remapch;
  mutable std::map<std::pair<int, int>, std::pair<int, int> > map_detid_and_detch;
    
  //detid_and_detch ->
  mutable std::map<std::pair<int, int>, int> map_detector_material;
  mutable std::map<std::pair<int, int>, int> map_detector_HV;

  mutable std::map<std::pair<int, int>, double> map_pos_x;
  mutable std::map<std::pair<int, int>, double> map_pos_y;
  mutable std::map<std::pair<int, int>, double> map_pos_z;

  mutable std::map<std::pair<int, int>, double> map_delta_x;
  mutable std::map<std::pair<int, int>, double> map_delta_y;
  mutable std::map<std::pair<int, int>, double> map_delta_z;

  mutable std::map<std::pair<int, int>, double> map_badch;

  mutable std::map<std::pair<int, int>, TSpline3*> map_calfunc;
};

} /* namespace hittree_gen*/

#endif 
