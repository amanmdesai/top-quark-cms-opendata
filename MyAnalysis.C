#define MyAnalysis_cxx
#include "MyAnalysis.h"
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
using namespace std;

MyAnalysis::MyAnalysis(){
  Init(m_chain);
}


void MyAnalysis::initialize(TString fileName){
//initialize the histograms, output trees

  //TFile *m_file = new TFile(filepath,"read");

  h_muon_mass = new TH1D(fileName+"_muon_mass",fileName+" _muon_mass", 40, 60, 120);
  h_NIsomuon = new TH1D(fileName+"_iso_muon",fileName+" _iso_muon", 10, 0, 10);


  m_chain = new TChain("events");
  m_chain->Add("files/"+fileName+".root");

} // end of initialize

void MyAnalysis::execute(){
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
    if(NIsomuon > 1){
    h_muon_mass->Fill((muon1 + muon2).M(),EventWeight);
    }
    }//chain loop
} // end of execute

void MyAnalysis::finalize(TString sample){
//finalize storage

TFile *store = new TFile("analysis.root","update");
h_muon_mass->Write();//sample+"_muon_mass",TObject::kWriteDelete);
h_NIsomuon->Write();//sample+"_iso_muon",TObject::kWriteDelete);
store->Write();
store->Close();

/*
TCanvas c1;
h_muon_mass->Draw("hist");
c1.SaveAs("hist.pdf");

TCanvas c2;
h_NIsomuon->Draw("hist");
c2.SaveAs("NIsomuon.pdf");
*/
}



MyAnalysis::~MyAnalysis(){
  //
  delete h_muon_mass;
  delete h_NIsomuon;
}
