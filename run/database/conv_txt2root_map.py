#!/usr/bin/env python
# coding: UTF-8

import sys
import ROOT

ROOT.gROOT.ProcessLine(\
    "struct map_t{\
    Int_t asicid;\
    Int_t asicch;\
    Int_t remapch;\
    Int_t detid;\
    Int_t detch;\
    };")

def main(infilename):
    infile = open(infilename,"r")
    outfilename = infilename.replace(".txt", ".root")
    outfile = ROOT.TFile(outfilename, "recreate")

    detector_map = ROOT.TTree("detector_map", "detector_map")

    map_t = ROOT.map_t()
    detector_map.Branch("asicid", ROOT.AddressOf(map_t, "asicid"), "asicid/I")
    detector_map.Branch("asicch", ROOT.AddressOf(map_t, "asicch"), "asicch/I")
    detector_map.Branch("remapch", ROOT.AddressOf(map_t, "remapch"), "remapch/I")
    detector_map.Branch("detid", ROOT.AddressOf(map_t, "detid"), "detid/I")
    detector_map.Branch("detch", ROOT.AddressOf(map_t, "detch"), "detch/I")

    infile.readline()

    for line in infile:
        linearray = line.split(" ")

        map_t.asicid = int(linearray[0])
        map_t.asicch = int(linearray[1])
        map_t.remapch = int(linearray[2])
        map_t.detid = int(linearray[3])
        map_t.detch = int(linearray[4])

        detector_map.Fill()

    outfile.Write()

if __name__=="__main__":
    infilename = sys.argv[1]
    main(infilename)

