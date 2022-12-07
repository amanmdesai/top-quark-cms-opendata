#ifndef JET_H
#define JET_H

#include <TLorentzVector.h>
#include <iostream>
class Jet: public TLorentzVector{

  public:
    Jet();
    Jet(double px, double py, double pz, double e){
      SetPxPyPzE(px, py, pz, e);
    };

    virtual ~Jet();
};

#endif
