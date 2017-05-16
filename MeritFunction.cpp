#include "MeritFunction.h"



void MeritFunction::setMeritFunction(int intParam){

    fDimension = 2;

    rDimension = 2;

    r.resize(rDimension);

    return;

}

void MeritFunction::updateR(Eigen::VectorXd& position){

    r(0) = position(0);
    r(1) = 10*position(0)/(position(0) + 0.1) + 2*position(1)*position(1);

    return;

}

double MeritFunction::f(){

    return r.transpose() * r; // r(0) + r(1);   MAKE SURE THIS DOESN'T WORK

}


void MeritFunction::printReport(Eigen::VectorXd& position){

    std::cout << "OPTIMIZATION RESULT: " << std::endl;
    std::cout << std::pow(position(0) * position(1) - 3,2) + 1.0 << std::endl << std::endl;
    std::cout << position << std::endl << std::endl;

    return;

}



Eigen::VectorXd MeritFunction::setInitialPosition(){

    Eigen::VectorXd position = Eigen::VectorXd::Random(fDimension);

    return position;

}


MeritFunction::MeritFunction(){



}
