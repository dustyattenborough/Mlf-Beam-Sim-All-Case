#!/usr/bin/env python
import ROOT
import sys

hSuffix = "_4pi"
hNames  = ["nuMuBarSpectrum", "nuMuSpectrum", "nuEBarSpectrum", "nuESpectrum"]
hTitles = ["#bar{#nu}_{#mu}", "#nu_{#mu}", "#bar{#nu}_{e}", "#nu_{e}"]
hColors = [ROOT.kBlack, ROOT.kRed, ROOT.kBlue, ROOT.kMagenta]

fName = sys.argv[1]
f = ROOT.TFile(fName)
hs = []
hStack = ROOT.THStack("hs", ";Energy [MeV];Entries")
for hName, hTitle, hColor in zip(hNames, hTitles, hColors):
    h = f.Get(hName+hSuffix)
    h.SetTitle(hTitle)
    h.SetLineColor(hColor)
    hStack.Add(h)

    hs.append(h)

c = ROOT.TCanvas("c", "c", 500, 500)
c.SetLogy()
c.SetGridx()
c.SetGridy()

hStack.Draw("nostack")
hStack.GetXaxis().SetRangeUser(0,300)

leg = c.BuildLegend(0.7, 0.7, 0.9, 0.85)
leg.SetFillStyle(0)
leg.SetLineWidth(0)

c.Modified()
c.Update()
#c.Draw()
c.SaveAs("TDR.png")
