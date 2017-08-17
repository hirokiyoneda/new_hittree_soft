#ifndef HitTreeGen_ReadHitTree_lv1_H
#define HitTreeGen_ReadHitTree_lv1_H 1

#include "BasicModule.hh"
#include "EventDataBuffer.hh"
#include "EventData_lv1.hh"
#include "ConstantPar.hh"
#include <string>
#include <fstream>
#include <vector>
#include "TChain.h"

class TFile;

namespace hittree_gen{

class ReadHitTree_lv1 : public anl::BasicModule
{
  DEFINE_ANL_MODULE(ReadHitTree_lv1, 1.0);
public:
  ReadHitTree_lv1();
  ~ReadHitTree_lv1() = default;

  anl::ANLStatus mod_startup();
  anl::ANLStatus mod_init();
  anl::ANLStatus mod_ana();

  int EventID() const { return m_EventID; }
  TChain* getTreePointer() const { return m_Tree; }

protected:
  std::string nextFile() { return *(m_FileIterator++); }
  bool wasLastFile() const { return (m_FileIterator==m_FileList.end()); }
  bool checkFiles();
  
private:
  const EventDataBuffer *eventDataBuffer_;
  EventData_lv1 *eventData;
  int m_EventID;
  std::vector<std::string> m_FileList;
  std::vector<std::string>::const_iterator m_FileIterator;

  TChain* m_Tree = nullptr;
  uint32_t m_NEvents = 0u;

  int nsignal = 0;
  int detid[MAX_N_SIGNAL];
  int detch[MAX_N_SIGNAL];
  int remapch[MAX_N_SIGNAL];
  int detector_material[MAX_N_SIGNAL];
  int detector_HV[MAX_N_SIGNAL];
  double pos_x[MAX_N_SIGNAL];
  double pos_y[MAX_N_SIGNAL];
  double pos_z[MAX_N_SIGNAL];
  double delta_x[MAX_N_SIGNAL];
  double delta_y[MAX_N_SIGNAL];
  double delta_z[MAX_N_SIGNAL];
  double epi[MAX_N_SIGNAL];
};

} /* namespace comptonsoft */

#endif 
