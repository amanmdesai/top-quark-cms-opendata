#ifndef MET_H
#define MET_H

#include <TLorentzVector.h>
#include <iostream>
class Met: public TLorentzVector{

  public:
    Met();
    Met(double metpx, double metpy){px = metpx; py = metpy;}
    double Met_Pt(){
      return sqrt(px*px + py*py);
    };

    virtual ~Met();
  private:
    double px, py;
};

#endif
