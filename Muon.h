#ifndef MUON_H
#define MUON_H

#include <TLorentzVector.h>
#include <iostream>
class Muon: public TLorentzVector{

  public:
    Muon();
    Muon(double px, double py, double pz, double e){
      SetPxPyPzE(px, py, pz, e);
    };

    const double muon_isolation(double isolation, double iso_cut){
      return (isolation/Pt()) < iso_cut;
    }

    virtual ~Muon();
};

#endif
