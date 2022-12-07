import ROOT

make_hist = {}

sample = ["data","ttbar","dy","wjets","ww","wz","zz","qcd","single_top"]

#legend_name = ["t\bar{t} Signal","wjets","dy","ww","wz","zz","qcd","single_top","data"]

color = [ROOT.kBlack,ROOT.kYellow, ROOT.kPink-3, ROOT.kGray, ROOT.kOrange, ROOT.kCyan, ROOT.kRed+1, ROOT.kGreen, ROOT.kBlue]
file = ROOT.TFile("analysis.root","READONLY")

histogram = ["_iso_muon", "_muon_mass","_muon_lead_pt","_muon_sublead_pt","_muon_lead_eta","_muon_sublead_eta","_MET","_Njet"]
Xtitle = ["Number of Muons", "m_{\mu\mu} [GeV]","Leading Muon Pt [GeV]","Subleading Muon Pt [GeV]", "Leading Muon \eta","Subleading Muon \eta","Missing transverse energy [GeV]","Number of Jets" ]
j=0
print(len(histogram))
for h in histogram:
    c1 = ROOT.TCanvas("c1","c1", 650,600)
    legend = ROOT.TLegend(0.68,0.60,0.98,0.9);
    legend.SetFillStyle(0);
    legend.SetBorderSize(0);
    make_stack = ROOT.THStack()
    for i in range(9):

        make_hist[sample[i]] = file.Get(sample[i]+h)
        make_hist[sample[i]].Sumw2()

        if(i==0):
            make_hist[sample[i]].SetMarkerStyle(20)
            make_hist[sample[i]].SetMarkerColor(color[i])
            entry=legend.AddEntry(make_hist[ sample[i] ],sample[i],"p")
        else:
            make_hist[sample[i]].SetFillColor(color[i])
            make_stack.Add(make_hist[sample[i]])
            entry=legend.AddEntry(make_hist[ sample[i] ],sample[i],"f")

    #make_hist["data"].SetMaximum(make_hist["data"].GetMaximum())
    make_stack.SetMaximum(make_hist["data"].GetMaximum()*5)

    ROOT.gStyle.SetOptStat(0)
    make_stack.Draw("hist")
    make_hist["data"].Draw("e1same")

    make_stack.GetXaxis().SetTitle(Xtitle[j])
    make_stack.GetYaxis().SetTitle("Events")
    #make_stack.GetXaxis().SetNdivisions(505)
    c1.SetLogy()
    make_stack.SetMinimum(1.01)
    #make_stack.SetMaximum(10e5)
    legend.Draw()
    if(j == 0):
        c1.SaveAs("plots.pdf(","pdf")
    elif(j == len(histogram)-1):
        c1.SaveAs("plots.pdf)","pdf")
    else:
        c1.SaveAs("plots.pdf","pdf")
    j = j+1
    del c1

    for i in range(9):
        del make_hist[sample[i]]

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
