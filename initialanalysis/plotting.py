import ROOT

file = ROOT.TFile("analysis.root","READONLY")
hist_muon_1 = file.Get("ww_muon_mass")
hist_muon_2 = file.Get("zz_muon_mass")
c1 = ROOT.TCanvas()
stack = ROOT.THStack()
#hist_muon_1.Draw("hist")
#hist_muon_2.Draw("hist same")
stack.Add(hist_muon_1)
stack.Add(hist_muon_2)
stack.Draw("hist")
c1.SaveAs("plots.pdf")
