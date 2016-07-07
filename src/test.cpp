#include <iostream>
#include <Eigen/Dense>
#include <typeinfo>
#include <string>
#include <vector>
#include "Hermite.h"
#include "EcgSigPrep.h"
#include "OrtCompresser.h"
#include "NelderMead.h"
#include <math.h>

#include "MatchingPursuit.h"

int main () {
	
	EcgSigPrep signal_handler("103", 2, 950);
	
	Eigen::MatrixXd sig = *signal_handler.getNextSegment();
	
	Hermite Herm(sig.cols());
	
	std::cout<<"HERM INIT DONE"<<std::endl;
	
	OrtCompresser OC(Herm, 50);
	
	std::cout<<"OC INIT DONE"<<std::endl;
	
	OrtCompressed* p;
	
	
	std::cout<<sig.transpose()<<std::endl;
	
	std::cout<<" "<<std::endl;
	
	sig = signal_handler.setDilatTrans(0.1, 155.0, Herm.get_ort_fun_roots(), sig); 
	
	p = OC.compressBeat(sig);
	
	p->trans = 155.0;
	p->dilat = 0.1;
	
	Eigen::MatrixXd apr = OC.decompress( p );
	
	std::cout<<apr.transpose()<<std::endl;
	
	
	return 0;
}
