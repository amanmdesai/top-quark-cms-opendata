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

  h_muon_mass = new TH1D(fileName+"_muon_mass",fileName+" _muon_mass", 60, 60, 120);
  h_NIsomuon = new TH1D(fileName+"_iso_muon",fileName+" _iso_muon", 7, 0, 7);
  h_muon_lead_pt = new TH1D(fileName+"_muon_lead_pt",fileName+" _muon_lead_pt", 90, 20, 200);
  h_muon_sublead_pt = new TH1D(fileName+"_muon_sublead_pt",fileName+" _muon_sublead_pt", 75, 0, 150);



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

    //Muons.clear();
    Int_t NIsomuon = 0;
    Muon muon1, muon2;

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
    if(NIsomuon > 1 && triggerIsoMu24 && muon1.Pt()>25.){

      h_muon_mass->Fill((muon1 + muon2).M(),EventWeight);
      h_muon_lead_pt->Fill(muon1.Pt(),EventWeight);
      h_muon_sublead_pt->Fill(muon2.Pt(),EventWeight);

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
