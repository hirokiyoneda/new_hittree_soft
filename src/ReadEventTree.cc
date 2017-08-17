#include "ReadEventTree.hh"

using namespace anl;

namespace hittree_gen 
{

ReadEventTree::ReadEventTree()
  : m_EventID(0),
  readDetectorDatabase_(nullptr),
  eventDataBuffer_(nullptr)
{
  add_alias("ReadEventTree");
}

ANLStatus ReadEventTree::mod_startup()
{
  register_parameter(&m_FileList, "file_list");
  return AS_OK;
}

ANLStatus ReadEventTree::mod_init()
{
  m_FileIterator = m_FileList.begin();

  m_Tree = new TChain("eventtree");
  while (!wasLastFile()) {
    m_Tree->Add(nextFile().c_str());
  }
  
  m_NEvents = m_Tree->GetEntries();
  std::cout << "Total Event : " << m_NEvents << std::endl;

  GetANLModule("ReadDetectorDatabase", &readDetectorDatabase_);
  GetANLModule("EventDataBuffer", &eventDataBuffer_);
  eventData = eventDataBuffer_->getEventData_lv0();

  nasic = readDetectorDatabase_->get_nasic();

  for(int iasic = 0; iasic < nasic; ++iasic){
      int asicid = readDetectorDatabase_->get_asicid(iasic); 

      std::ostringstream oss;
      oss << "adc" << asicid;
      std::string branchName = oss.str();
      m_Tree->SetBranchAddress(branchName.c_str(), m_ADC[iasic]);
      std::cout << branchName << std::endl;

      oss.str("");
      oss << "index" << asicid;
      branchName = oss.str();
      m_Tree->SetBranchAddress(branchName.c_str(), m_INDEX[iasic]);
      std::cout << branchName << std::endl;

      oss.str("");
      oss << "hitnum" << asicid;
      branchName = oss.str();
      m_Tree->SetBranchAddress(branchName.c_str(), &m_HITNUM[iasic]);
      std::cout << branchName << std::endl;
      
      oss.str("");
      oss << "cmn" << asicid;
      branchName = oss.str();
      m_Tree->SetBranchAddress(branchName.c_str(), &m_CMN[iasic]);
      std::cout << branchName << std::endl;
  }

  return AS_OK;
}

ANLStatus ReadEventTree::mod_ana()
{
  ++m_EventID;
  static unsigned int iEvent = 0;
  if(iEvent == m_NEvents) {
    return AS_QUIT;
  }

  eventData->ResetData();

  m_Tree->GetEntry(iEvent);

  int nsignal = 0;
  for(int iasic = 0; iasic < nasic; ++iasic){
      int hitnum = (int)m_HITNUM[iasic];

      if(hitnum == 0){
        continue;
      }

      for(int ich = 0; ich < hitnum; ++ich){
          ++nsignal;
          int asicid = readDetectorDatabase_->get_asicid(iasic); 
          int asicch = (int)m_INDEX[iasic][ich];
          int adc = (int)m_ADC[iasic][ich] - (int)m_CMN[iasic];

          eventData->set_asicid(asicid);
          eventData->set_asicch(asicch);
          eventData->set_adc(adc);
      }
  }
  eventData->set_nsignal(nsignal);
  
  iEvent++;
  return AS_OK;
}

bool ReadEventTree::checkFiles()
{
  for (auto& filename: m_FileList) {
    std::ifstream fin;
    fin.open( filename.c_str() );
    if (!fin) {
      std::cout << "ReadEventTree: cannot open " << filename << std::endl;
      return false;
    }
    fin.close();
  }
  return true;
}

} /* namespace hittree_gen*/
