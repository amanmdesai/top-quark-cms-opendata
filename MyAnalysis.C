#define MyAnalysis_cxx
#include "MyAnalysis.h"
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
using namespace std;

MyAnalysis::MyAnalysis(){
  Init(m_chain);
}


void MyAnalysis::initialize(){
//initialize the histograms, output trees

  //TFile *m_file = new TFile(filepath,"read");

  //TTree *m_tree = (TTree*)m_file->Get("events");
  m_chain = new TChain("events");
  m_chain->Add("files/dy.root");
  //fChain->Get("events")
  //fChain->SetBranchAddress("NMuon",&NMuon);

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

    if(NIsomuon > 1){
    h_muon_mass->Fill((muon1 + muon2).M(),EventWeight);
    }
    }//chain loop
} // end of execute

void MyAnalysis::finalize(){
//initialize the codes
TCanvas c;
h_muon_mass->Draw("hist");
c.SaveAs("hist.pdf");
}



MyAnalysis::~MyAnalysis(){
  //
}
