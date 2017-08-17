%module eventTree2HitTreeGen 
%{
#include "BasicModule.hh"

// include headers of my modules
#include "EventDataBuffer.hh"
#include "DataProcess_lv1.hh"
#include "DataProcess_lv2_base.hh"
#include "DataProcess_lv2_merge.hh"
#include "DataProcess_lv3_base.hh"
#include "DataProcess_lv3_reconstruct.hh"
#include "ReadDetectorDatabase.hh"
#include "ReadEventTree.hh"
#include "ReadHitTree_lv1.hh"
#include "ReadHitTree_lv2.hh"
#include "SaveData.hh"
#include "WriteHitTree_lv1.hh"
#include "WriteHitTree_lv2.hh"
#include "WriteHitTree_lv3.hh"

%}

%import "ANL.i"


// interface to my modules


namespace hittree_gen {

class EventDataBuffer: public anl::BasicModule
{
public:
    EventDataBuffer();
    ~EventDataBuffer();
};

class DataProcess_lv1 : public anl::BasicModule
{
public:
    DataProcess_lv1();
    ~DataProcess_lv1();
};

class DataProcess_lv2_base : public anl::BasicModule
{
public:
    DataProcess_lv2_base();
    ~DataProcess_lv2_base();
};

class DataProcess_lv2_merge : public DataProcess_lv2_base
{
public:
    DataProcess_lv2_merge();
    ~DataProcess_lv2_merge();
};

class DataProcess_lv3_base : public anl::BasicModule
{
public:
    DataProcess_lv3_base();
    ~DataProcess_lv3_base();
};

class DataProcess_lv3_reconstruct : public DataProcess_lv3_base
{
public:
    DataProcess_lv3_reconstruct();
    ~DataProcess_lv3_reconstruct();
};

class ReadDetectorDatabase : public anl::BasicModule
{
public:
    ReadDetectorDatabase();
    ~ReadDetectorDatabase();
};

class ReadEventTree : public anl::BasicModule
{
public:
    ReadEventTree();
    ~ReadEventTree();
};

class ReadHitTree_lv1 : public anl::BasicModule
{
public:
    ReadHitTree_lv1();
    ~ReadHitTree_lv1();
};

class ReadHitTree_lv2 : public anl::BasicModule
{
public:
    ReadHitTree_lv2();
    ~ReadHitTree_lv2();
};

class SaveData : public anl::BasicModule
{
public:
    SaveData();
    ~SaveData();
};

class WriteHitTree_lv1 : public anl::BasicModule
{
public:
    WriteHitTree_lv1();
    ~WriteHitTree_lv1();
};

class WriteHitTree_lv2 : public anl::BasicModule
{
public:
    WriteHitTree_lv2();
    ~WriteHitTree_lv2();
};

class WriteHitTree_lv3 : public anl::BasicModule
{
public:
    WriteHitTree_lv3();
    ~WriteHitTree_lv3();
};

}
