#!/usr/bin/env python
# coding: UTF-8

import sys
import ROOT

ROOT.gROOT.ProcessLine(\
    "struct profile_t{\
    Int_t detid;\
    Int_t detch;\
    Int_t detector_material;\
    Int_t detector_HV ;\
    Double_t pos_x ;\
    Double_t pos_y ;\
    Double_t pos_z ;\
    Double_t delta_x ;\
    Double_t delta_y ;\
    Double_t delta_z ;\
    Int_t badch;\
    };")

def main(infilename):
    infile = open(infilename,"r")
    outfilename = infilename.replace(".txt", ".root")
    outfile = ROOT.TFile(outfilename, "recreate")

    detector_profile = ROOT.TTree("detector_profile", "detector_profile")

    profile_t = ROOT.profile_t()
    detector_profile.Branch("detid", ROOT.AddressOf(profile_t, "detid"), "detid/I")
    detector_profile.Branch("detch", ROOT.AddressOf(profile_t, "detch"), "detch/I")
    detector_profile.Branch("detector_material", ROOT.AddressOf(profile_t, "detector_material"), "detector_material/I")
    detector_profile.Branch("detector_HV", ROOT.AddressOf(profile_t, "detector_HV"), "detector_HV/I")
    detector_profile.Branch("pos_x", ROOT.AddressOf(profile_t, "pos_x"), "pos_x/D")
    detector_profile.Branch("pos_y", ROOT.AddressOf(profile_t, "pos_y"), "pos_y/D")
    detector_profile.Branch("pos_z", ROOT.AddressOf(profile_t, "pos_z"), "pos_z/D")
    detector_profile.Branch("delta_x", ROOT.AddressOf(profile_t, "delta_x"), "delta_x/D")
    detector_profile.Branch("delta_y", ROOT.AddressOf(profile_t, "delta_y"), "delta_y/D")
    detector_profile.Branch("delta_z", ROOT.AddressOf(profile_t, "delta_z"), "delta_z/D")
    detector_profile.Branch("badch", ROOT.AddressOf(profile_t, "badch"), "badch/I")

    infile.readline()

    for line in infile:
        linearray = line.split(" ")

        profile_t.detid = int(linearray[0])
        profile_t.detch = int(linearray[1])
        profile_t.detector_material = int(linearray[2])
        profile_t.detector_HV = int(linearray[3])
        profile_t.pos_x = float(linearray[4])
        profile_t.pos_y = float(linearray[5])
        profile_t.pos_z = float(linearray[6])
        profile_t.delta_x = float(linearray[7])
        profile_t.delta_y = float(linearray[8])
        profile_t.delta_z = float(linearray[9])
        profile_t.badch = int(linearray[10])

        detector_profile.Fill()

    outfile.Write()

if __name__=="__main__":
    infilename = sys.argv[1]
    main(infilename)

