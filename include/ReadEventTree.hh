#ifndef HitTreeGen_ReadEventTree_H
#define HitTreeGen_ReadEventTree_H 1

#include "BasicModule.hh"
#include "EventData_lv0.hh"
#include "ReadDetectorDatabase.hh"
#include "EventDataBuffer.hh"
#include "ConstantPar.hh"
#include <string>
#include <fstream>
#include <vector>
#include "TChain.h"

class TFile;

namespace hittree_gen{

class ReadEventTree : public anl::BasicModule
{
  DEFINE_ANL_MODULE(ReadEventTree, 1.0);
public:
  ReadEventTree();
  ~ReadEventTree() = default;

  anl::ANLStatus mod_startup();
  anl::ANLStatus mod_init();
  anl::ANLStatus mod_ana();

  int EventID() const { return m_EventID; }
  TChain* getTreePointer() const { return m_Tree; }
//  EventData_lv0* getEventData() const { return eventData; }

protected:
  std::string nextFile() { return *(m_FileIterator++); }
  bool wasLastFile() const { return (m_FileIterator==m_FileList.end()); }
  bool checkFiles();
  
private:
  EventData_lv0 *eventData;
  const ReadDetectorDatabase *readDetectorDatabase_;
  const EventDataBuffer *eventDataBuffer_;
  int m_EventID;
  std::vector<std::string> m_FileList;
  std::vector<std::string>::const_iterator m_FileIterator;

  int nasic = 0;

  TChain* m_Tree = nullptr;
  uint32_t m_NEvents = 0u;
  uint16_t m_ADC[MAX_N_ASIC][N_ASICCH];
  uint16_t m_INDEX[MAX_N_ASIC][N_ASICCH];
  uint16_t m_HITNUM[MAX_N_ASIC];
  uint16_t m_CMN[MAX_N_ASIC];
  unsigned int m_UnixTime = 0;
  unsigned int m_LiveTime;
  unsigned int m_IntegralLiveTime;
  unsigned int m_Ti;
};

} /* namespace comptonsoft */

#endif 
