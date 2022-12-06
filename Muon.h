#ifndef MUON_H
#define MUON_H

#include <TLorentzVector.h>

class Muon: public TLorentzVector{

  public:
    Muon();
    Muon(double px, double py, double pz, double e)
    {
      SetPxPyPzE(px, py, pz, e);
    }
    ;
    virtual ~Muon();
};

#endif
