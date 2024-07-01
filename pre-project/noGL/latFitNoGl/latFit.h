#include "biu/Point.hh"
#include "biu/Matrix.hh"//  <Matrix.hh>
#include "biu/Rotator3D.hh"
#include "biu/OptionParser.hh"
#include "biu/LatticeDescriptorSQR.hh"
#include "biu/LatticeDescriptorCUB.hh"
#include "biu/LatticeDescriptorFCC.hh"
#include "biu/LatticeDescriptorCKW.hh"
#include "biu/LatticeModel.hh"

#include "biu/LatticeProteinUtil.hh"
#include "biu/SuperPos_Kabsch.hh"

std::pair<double, double> mainLatFit( int argc, char** argv );

biu::DblPoint getCentroid( const biu::DPointVec& sc );
