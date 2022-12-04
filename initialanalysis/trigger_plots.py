#from ROOT import TFile,TTree,TCanvas,TH1D,TColor, TLegend
import ROOT
sample = ["dy","qcd","single_top","ttbar","wjets","ww","wz","zz","data"]

#muon_mass = TH1D("muon_mass","muon_mass",100,0,120)
hist_muon = {}
#for i in range(9):
#    hist_muon[].append(TH1D(sample[i]+"mass",sample[i]+"mass",100,10,120))
color = [ROOT.kYellow, ROOT.kPink, ROOT.kGray, ROOT.kOrange, ROOT.kCyan, ROOT.kRed, ROOT.kGreen, ROOT.kBlue,ROOT.kBlack]
stack_muon = ROOT.THStack()
file = ROOT.TFile("analysis.root","READONLY")
c1 = ROOT.TCanvas("c1","c1", 650,600)
legend = ROOT.TLegend(0.7,0.70,0.98,0.9);
legend.SetFillStyle(0);
legend.SetBorderSize(0);

for i in range(9):
    print(i, sample[i])
    hist_muon[sample[i]] = file.Get(sample[i]+"_num_muon")
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


    #c1.Update

#legend.Draw()
#stack_muon.Add(hist_muon)
#stack_muon.GetXaxis().SetRange(60,120)
#hist_muon["data"].GetXaxis().SetRange(60,120)
stack_muon.Draw()
hist_muon["data"].Draw("e1same")
c1.SetLogy()
stack_muon.SetMinimum(1)
stack_muon.SetMaximum(10e5)
#for i in range(9):
legend.Draw()

c1.SaveAs("muon_mass.pdf")
#for hist in range(9):
    #hist_muon[hist].Draw("hist same")

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
