from ROOT import TFile,TTree,TCanvas,TH1D,TColor
import ROOT
sample = ["data","dy","qcd","single_top","ttbar","wjets","ww","wz","zz"]

#muon_mass = TH1D("muon_mass","muon_mass",100,0,120)
c1 = TCanvas()
hist_muon = []
for i in range(9):
    hist_muon.append(TH1D(sample[i]+"mass",sample[i]+"mass",100,10,120))
color = [ROOT.kBlack,ROOT.kYellow, ROOT.kPink, ROOT.kGray, ROOT.kOrange, ROOT.kCyan, ROOT.kRed, ROOT.kGreen, ROOT.kBlue]
#stack_muon = ROOT.THStack("mass muon","muon mass");
legend = ROOT.TLegend(0.75,0.7,0.98,0.9);
legend.SetFillStyle(0);
legend.SetBorderSize(0);

for i in range(9):
    print(i, sample[i])
    file = TFile(sample[i]+".root","read")
    hist_muon = file.Get("h_muon_mass")
    if(i==1):
        hist_muon.SetMarkerStyle(8)
        hist_muon.SetMarkerColor(color[i])
        hist_muon.Draw()
        #legend.AddEntry(hist_muon,sample[i]);
    else:
        hist_muon.SetFillColor(color[i])
        hist_muon.Draw("same")
        #legend.AddEntry(hist_muon,sample[i]);
    c1.Update()

#legend.Draw()
#stack_muon.Add(hist_muon)
#stack_muon.Draw("hist")
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
