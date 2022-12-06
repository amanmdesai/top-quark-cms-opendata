#from ROOT import TFile,TTree,TCanvas,TH1D,TColor, TLegend
import ROOT
sample = ["ttbar","wjets","dy","ww","wz","zz","qcd","single_top","data"]
#muon_mass = TH1D("muon_mass","muon_mass",100,0,120)
hist_muon = {}
#for i in range(9):
#    hist_muon[].append(TH1D(sample[i]+"mass",sample[i]+"mass",100,10,120))
color = [ROOT.kYellow, ROOT.kPink, ROOT.kGray, ROOT.kOrange, ROOT.kCyan, ROOT.kRed, ROOT.kGreen, ROOT.kBlue,ROOT.kBlack]
file = ROOT.TFile("analysis.root","READONLY")

histogram = ["_iso_muon","_iso_muon", "_muon_mass"]
Xtitle = ["Number of Muons","Number of Muons", "m_{\mu\mu}"]
j=0
for h in histogram:
    c1 = ROOT.TCanvas("c1","c1", 650,600)
    legend = ROOT.TLegend(0.7,0.70,0.98,0.9);
    legend.SetFillStyle(0);
    legend.SetBorderSize(0);
    stack_muon = ROOT.THStack()
    for i in range(9):
        print(i, sample[i])
        hist_muon[sample[i]] = file.Get(sample[i]+h)
        print(hist_muon)
        if(i==8):
            hist_muon[sample[i]].SetMarkerStyle(20)
            hist_muon[sample[i]].SetMarkerColor(color[i])
            hist_muon[sample[i]].Sumw2()
            entry=legend.AddEntry(hist_muon[ sample[i] ],sample[i],"p")
            #hist_muon[sample[i]].Draw("psame")
            #stack_muon.Add(hist_muon[sample[i]])
            #legend.AddEntry(hist_muon,sample[i]);
        else:
            hist_muon[sample[i]].SetFillColor(color[i])
            entry=legend.AddEntry(hist_muon[ sample[i] ],sample[i],"f")
            #hist_muon[sample[i]].Draw("same")
            #legend.AddEntry(hist_muon,sample[i]);
            stack_muon.Add(hist_muon[sample[i]])
            #hist_muon[sample[i]].Draw("same hist")
            #hist_muon[sample[i]].GetXaxis().SetRange(60,120)


    ROOT.gStyle.SetOptStat(0)
    stack_muon.Draw("hist")
    hist_muon["data"].Draw("e1same")
    stack_muon.GetXaxis().SetTitle(Xtitle[j])
    c1.SetLogy()
    stack_muon.SetMinimum(1)
    stack_muon.SetMaximum(10e5)
    legend.Draw()
    #c1.SaveAs("h"+h+".pdf")
    if(j == 0):
        c1.SaveAs("plots.pdf(","pdf")
    elif(j == 2):
        c1.SaveAs("plots.pdf)","pdf")
    else:
        c1.SaveAs("plots.pdf","pdf")
    j = j+1

'''
filepath = "files/data.root"
m_file = ROOT.TFile.Open(filepath,"read")
m_tree = m_file.events
num_entries = m_tree.GetEntries()
print(num_entries)

for entry in range(0,num_entries):
    m_tree.GetEntry(entry)
    v1 = m_tree.getattr(m_tree,"Muon_Iso")
'''
