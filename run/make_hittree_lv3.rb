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
    @outfilename = File.basename(@filename,"_hittree_lv2.root")+"_hittree_lv3.root"

    chain :SaveData
    with_parameters(output: @outfilename)    

    chain :EventDataBuffer

    chain :ReadHitTree_lv2
    with_parameters(file_list: [@filename])    

    chain :DataProcess_lv3_reconstruct

    chain :WriteHitTree_lv3

  end
end

anl = MyApp.new
anl.write_parameters_to_json "parameters.json"
anl.run(-1, 1000)
