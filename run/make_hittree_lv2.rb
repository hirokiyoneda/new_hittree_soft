#!/usr/bin/env ruby

#require 'comptonsoft/basic'
#include ComptonSoft
#
require 'ANLLib'
require 'eventTree2HitTreeGen'
include EventTree2HitTreeGen

#analysis_param="database/analysis_parameters.xml"

class MyApp < ANL::ANLApp

  def setup()
    @filename = ARGV[0]
    @outfilename = File.basename(@filename,"_hittree_lv1.root")+"_hittree_lv2.root"

    chain :SaveData
    with_parameters(output: @outfilename)    

    chain :EventDataBuffer

    chain :ReadHitTree_lv1
    with_parameters(file_list: [@filename])    

    chain :DataProcess_lv2_merge
    with_parameters(Threshold_Si_0V: 5.0,
                    Threshold_Si_HV: 5.0,
                    Threshold_CdTe_0V: 5.0,
                    Threshold_CdTe_HV: 5.0)

    chain :WriteHitTree_lv2

  end
end

anl = MyApp.new
anl.write_parameters_to_json "parameters.json"
anl.run(-1, 1000)
