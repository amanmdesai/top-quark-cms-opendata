#include "MyAnalysis.h"
#include <iostream>
int main(){
MyAnalysis *A = new MyAnalysis();
A->initialize();
A->execute();
A->finalize();
return 0;
}
