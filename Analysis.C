#define Analysis_cxx
#include "Analysis.h"
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
using namespace std;

Analysis::Analysis(){
  Init(m_chain);
}


void Analysis::initialize(TString fileName){
//initialize the histograms, output trees

  //TFile *m_file = new TFile(filepath,"read");

  h_muon_mass = new TH1D(fileName+"_muon_mass",fileName+" _muon_mass", 75, 0, 150);
  h_NIsomuon = new TH1D(fileName+"_iso_muon",fileName+" _iso_muon", 7, 0, 7);
  h_muon_lead_pt = new TH1D(fileName+"_muon_lead_pt",fileName+" _muon_lead_pt", 90, 20, 200);
  h_muon_sublead_pt = new TH1D(fileName+"_muon_sublead_pt",fileName+" _muon_sublead_pt", 75, 0, 150);

  h_muon_lead_eta = new TH1D(fileName+"_muon_lead_eta",fileName+" _muon_lead_eta", 30, -3, 3);
  h_muon_sublead_eta = new TH1D(fileName+"_muon_sublead_eta",fileName+" _muon_sublead_eta", 30, -3, 3);

  h_MET = new TH1D(fileName+"_MET",fileName+" _MET", 10, 0, 100);

  h_Njet = new TH1F(fileName+"_Njet",fileName+" _Njet", 10, 0, 10);



  m_chain = new TChain("events");
  m_chain->Add("files/"+fileName+".root");

} // end of initialize

void Analysis::execute(){
//run the analysis code here
  if(!m_chain) {
    throw std::runtime_error("chain not initialized");
    }
  Init(m_chain);

  for(Int_t event=0; event < fChain->GetEntries() ; event++){

    fChain->GetEntry(event);


    Int_t NIsomuon = 0;
    Muon muon1, muon2;

    Met MET(MET_px, MET_py);
    if(MET.Met_Pt() < 30) continue;
    if(NJet < 2) continue;
    if(NMuon < 2) continue;

    h_MET->Fill(MET.Met_Pt(),EventWeight);
    h_Njet->Fill(NJet,EventWeight);


    for(int muon=0; muon < NMuon; ++muon){
      Muon good_muon(Muon_Px[muon],Muon_Py[muon],Muon_Pz[muon],Muon_E[muon]);
      if(good_muon.muon_isolation(Muon_Iso[muon], .10)){
        ++NIsomuon;
        if(NIsomuon==1){ muon1 = good_muon ;}
        if(NIsomuon==2){ muon2 = good_muon ;}
        }
    }//muon loop ends here
    //std::cout << NIsomuon << std::endl;
    h_NIsomuon->Fill(NIsomuon,EventWeight);

    if(NIsomuon > 1 && triggerIsoMu24 && muon1.Pt()>25. && abs(muon1.Eta())<2.4 && abs(muon1.Eta())<2.4){
      double mass = (muon1 + muon2).M();
      if(mass > 106 || mass < 76 || mass < 12){
        h_muon_mass->Fill(mass,EventWeight);
        h_muon_lead_pt->Fill(muon1.Pt(),EventWeight);
        h_muon_sublead_pt->Fill(muon2.Pt(),EventWeight);
        h_muon_lead_eta->Fill(muon1.Eta(),EventWeight);
        h_muon_sublead_eta->Fill(muon2.Eta(),EventWeight);
      }

    }//muon filling

  }//chain loop

} // end of execute

void Analysis::finalize(TString sample){
//finalize storage

TFile *store = new TFile("analysis.root","update");
h_muon_mass->Write();
h_NIsomuon->Write();
h_muon_lead_pt->Write();
h_muon_sublead_pt->Write();
h_muon_lead_eta->Write();
h_muon_sublead_eta->Write();
h_MET->Write();
h_Njet->Write();
store->Write();
store->Close();
//sample+"_iso_muon",TObject::kWriteDelete);

/*
TCanvas c1;
h_muon_mass->Draw("hist");
c1.SaveAs("hist.pdf");

TCanvas c2;
h_NIsomuon->Draw("hist");
c2.SaveAs("NIsomuon.pdf");
*/
}



Analysis::~Analysis(){
  //
  delete h_muon_mass;
  delete h_NIsomuon;

  delete h_muon_lead_pt;
  delete h_muon_sublead_pt;


}
