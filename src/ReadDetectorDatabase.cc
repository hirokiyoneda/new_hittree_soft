#include "ReadDetectorDatabase.hh"

using namespace anl;

namespace hittree_gen
{

ReadDetectorDatabase::ReadDetectorDatabase()
  : map_Filename("map.root"),
    profile_Filename("profile.root"),
    calfunc_Filename("calfunc.root"),
    map_File(nullptr),
    profile_File(nullptr),
    calfunc_File(nullptr)
{
}

ANLStatus ReadDetectorDatabase::mod_startup()
{
  register_parameter(&map_Filename, "map_file");
  register_parameter(&profile_Filename, "profile_file");
  register_parameter(&calfunc_Filename, "calfunc_file");
  return AS_OK;
}

ANLStatus ReadDetectorDatabase::mod_init()
{
  map_File = new TFile(map_Filename.c_str(), "r");
  profile_File = new TFile(profile_Filename.c_str(), "r");
  calfunc_File = new TFile(calfunc_Filename.c_str(), "r");

  if( !map_File ){
    std::cout << "ReadDetectorDatabase: cannot read " << map_Filename << std::endl;
    return AS_QUIT;
  }
  if( !profile_File ){
    std::cout << "ReadDetectorDatabase: cannot read " << profile_Filename << std::endl;
    return AS_QUIT;
  }
  if( !calfunc_File ){
    std::cout << "ReadDetectorDatabase: cannot read " << calfunc_Filename << std::endl;
    return AS_QUIT;
  }

  detector_map = (TTree*)map_File->Get("detector_map");
  detector_profile = (TTree*)profile_File->Get("detector_profile");

  if( !detector_map){
    std::cout << "ReadDetectorDatabase: cannot find TTree::detector_map" << std::endl;
    return AS_QUIT;
  }
  if( !detector_profile){
    std::cout << "ReadDetectorDatabase: cannot find TTree::detector_profile" << std::endl;
    return AS_QUIT;
  }

  load_Map_Databese();
  load_Profile_Databese();
  load_Calfunc_Databese();

  return AS_OK;
}

void ReadDetectorDatabase::load_Map_Databese(){
    detector_map->SetBranchAddress("asicid", &asicid);
    detector_map->SetBranchAddress("asicch", &asicch);
    detector_map->SetBranchAddress("remapch", &remapch);
    detector_map->SetBranchAddress("detid", &detid);
    detector_map->SetBranchAddress("detch", &detch);

    Long64_t nch = detector_map->GetEntries();

    for(Long64_t ich = 0; ich < nch; ++ich){
        detector_map->GetEntry(ich);

        std::pair<int, int> p_asicid_and_asicch = std::make_pair(asicid, asicch);

        vec_asicid.push_back(asicid);

        vec_asicid_and_asicch.push_back(p_asicid_and_asicch);

        map_remapch[p_asicid_and_asicch] = remapch;
        map_detid_and_detch[p_asicid_and_asicch] = std::make_pair(detid, detch);
    }

    std::sort(vec_asicid.begin(), vec_asicid.end());
    vec_asicid.erase(std::unique(vec_asicid.begin(), vec_asicid.end()), vec_asicid.end());

    std::cout << "ASICID : " << std::flush;
    for(auto itr = vec_asicid.begin(); itr != vec_asicid.end(); ++itr){
        std::cout << *itr << " " << std::flush;
    }
    std::cout << std::endl;

    nasic = vec_asicid.size();
}

void ReadDetectorDatabase::load_Profile_Databese(){
    detector_profile->SetBranchAddress("detid", &detid);
    detector_profile->SetBranchAddress("detch", &detch);
    detector_profile->SetBranchAddress("detector_material", &detector_material);
    detector_profile->SetBranchAddress("detector_HV", &detector_HV);
    detector_profile->SetBranchAddress("pos_x", &pos_x);
    detector_profile->SetBranchAddress("pos_y", &pos_y);
    detector_profile->SetBranchAddress("pos_z", &pos_z);
    detector_profile->SetBranchAddress("delta_x", &delta_x);
    detector_profile->SetBranchAddress("delta_y", &delta_y);
    detector_profile->SetBranchAddress("delta_z", &delta_z);
    detector_profile->SetBranchAddress("badch", &badch);

    Long64_t nch = detector_profile->GetEntries();

    for(Long64_t ich = 0; ich < nch; ++ich){
        detector_profile->GetEntry(ich);

        std::pair<int, int> p_detid_and_detch = std::make_pair(detid, detch);

        map_detector_material[p_detid_and_detch] = detector_material;
        map_detector_HV[p_detid_and_detch] = detector_HV;

        map_pos_x[p_detid_and_detch] = pos_x;
        map_pos_y[p_detid_and_detch] = pos_y;
        map_pos_z[p_detid_and_detch] = pos_z;

        map_delta_x[p_detid_and_detch] = delta_x;
        map_delta_y[p_detid_and_detch] = delta_y;
        map_delta_z[p_detid_and_detch] = delta_z;

        map_badch[p_detid_and_detch] = badch;
    }
}

void ReadDetectorDatabase::load_Calfunc_Databese(){
    for(auto itr = vec_asicid_and_asicch.begin(); itr != vec_asicid_and_asicch.end(); ++itr){
        if(isBlackch(*itr)){
            continue;
        }

        int detid = get_detid(*itr);
        int detch = get_detch(*itr);
        std::pair<int, int> p_detid_and_detch = std::make_pair(detid, detch);

        std::ostringstream oss;
        oss.str("");
        oss << "calfunc_" << detid << "_" << detch;
        std::string branchName = oss.str();

        TSpline3 *calfunc = (TSpline3*)calfunc_File->Get(branchName.c_str());
        if( !calfunc){
            std::cout << "ReadDetectorDatabase: cannot find calfunc:" << branchName << std::endl;
        }
        map_calfunc[*itr] = calfunc;  
    }
}

} /* namespace hittree_gen*/
