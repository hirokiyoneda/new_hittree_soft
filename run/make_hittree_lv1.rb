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
    @outfilename = File.basename(@filename,".root")+"_hittree_lv1.root"
    @map_filename = "map.root"
    @profile_filename = "profile.root"
    @calfunc_filename = "rename_spline_maxbin_no17.root"

    chain :SaveData
    with_parameters(output: @outfilename)    

    chain :EventDataBuffer

    chain :ReadDetectorDatabase
    with_parameters(map_file: @map_filename,
                    profile_file: @profile_filename,
                    calfunc_file: @calfunc_filename)    

    chain :ReadEventTree
    with_parameters(file_list: [@filename])    

    chain :DataProcess_lv1

    chain :WriteHitTree_lv1

  end
end

anl = MyApp.new
anl.write_parameters_to_json "parameters.json"
anl.run(-1, 1000)
