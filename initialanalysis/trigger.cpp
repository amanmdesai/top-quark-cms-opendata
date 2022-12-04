
using namespace std;

void trigger(const char *filepath, TString sample){
//TString filepath = "files/data.root";
//TString sample[9] = {"data","dy","qcd","single_top","ttbar","wjets","ww","w","zz"};
TFile *m_file = new TFile(filepath,"read");

TTree *m_tree = (TTree*)m_file->Get("events");

cout << "processing "<<sample<<" containing " << m_tree->GetEntries()<<" with entries "<<endl;

Int_t NMuon;
Double_t muon_mass;
Float_t Muon_Iso[3];
Float_t Muon_Px[3];
Float_t Muon_Py[3];
Float_t Muon_Pz[3];
Float_t Muon_E[3];
Double_t Muon_Pt;
m_tree->SetBranchAddress("NMuon",&NMuon);
m_tree->SetBranchAddress("Muon_Iso",&Muon_Iso);

m_tree->SetBranchAddress("Muon_Px",&Muon_Px);
m_tree->SetBranchAddress("Muon_Py",&Muon_Py);
m_tree->SetBranchAddress("Muon_Pz",&Muon_Pz);
m_tree->SetBranchAddress("Muon_E",&Muon_E);

TLorentzVector muon_1;
TLorentzVector muon_2;


TH1 *h_muon_iso = new TH1F("h_iso_muon","h_iso_muon",40,-1,-1);
TH1 *h_num_muon = new TH1F("h_num_muon","h_num_muon",7,0,7);
TH1 *h_muon_mass = new TH1F("h_muon_mass","h_muon_mass",50,10,160);


for(int i=0; i <m_tree->GetEntries(); i++){

  m_tree->GetEntry(i);

  //if(NMuon == 0) continue;
  h_num_muon->Fill(NMuon);

  for(Int_t muon=0; muon < NMuon; muon++){
    Muon_Pt = sqrt(Muon_Px[muon]*Muon_Px[muon] + Muon_Py[muon]*Muon_Py[muon]);
    if(Muon_Pt < 25) continue;
    if((Muon_Iso[muon]/Muon_Pt) > .1) continue;
    h_muon_iso->Fill(Muon_Iso[muon]);
  }

  if(NMuon>=1){
    muon_1.SetPxPyPzE(Muon_Px[0],Muon_Py[0],Muon_Pz[0],Muon_E[0]);
    muon_2.SetPxPyPzE(Muon_Px[1],Muon_Py[1],Muon_Pz[1],Muon_E[1]);
    muon_mass = (muon_1 + muon_2).M();
    //cout << muon_mass <<endl;
    h_muon_mass->Fill(muon_mass);

  }


}


TFile *save = new TFile("analysis.root","update");
h_muon_iso->SetName(sample+"_muon_iso");
h_num_muon->SetName(sample+"_num_muon");
h_muon_mass->SetName(sample+"_muon_mass");
h_muon_iso->Write(sample+"_muon_iso",TObject::kWriteDelete);
h_num_muon->Write(sample+"_num_muon",TObject::kWriteDelete);
h_muon_mass->Write(sample+"_muon_mass",TObject::kWriteDelete);
save->Write();
save->Close();

/*
TCanvas c1;
h_muon_iso->Draw("hist");
c1.SaveAs(sample+"_muon_iso.pdf");
TCanvas c2;
h_num_muon->Draw("hist");
c2.SetLogy();
c2.SaveAs(sample+"_muons.pdf");

TCanvas c3;
h_muon_mass->Draw("hist");
c3.SaveAs(sample+"_muon_mass.pdf");

*/
}
