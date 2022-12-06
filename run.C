#include "MyAnalysis.h"
#include <iostream>
int main(){

MyAnalysis A[9];
TString sample[9] = {"data","ttbar","dy","qcd","single_top","wjets","ww","wz","zz"};
for(Int_t i=0; i < 9; i++){
  A[i].initialize(sample[i]);
  A[i].execute();
  A[i].finalize(sample[i]);
};

/*MyAnalysis *A = new MyAnalysis();
A->initialize("dy");
A->execute();
A->finalize("dy");
*/

return 0;
}
