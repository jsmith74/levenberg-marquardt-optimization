#include "MeritFunction.h"



void MeritFunction::setMeritFunction(){

    fDimension = 2;

    rDimension = 2;

    return;

}

void MeritFunction::updateR(Eigen::VectorXd& position,Eigen::VectorXd& r){

    r(0) = position(0);
    r(1) = 10*position(0)/(position(0) + 0.1) + 2*position(1)*position(1);

    return;

}



void MeritFunction::printResult(Eigen::VectorXd& position,Eigen::VectorXd& r){

    std::cout << std::endl << std::endl << std::endl;

    r(0) = position(0);
    r(1) = 10*position(0)/(position(0) + 0.1) + 2*position(1)*position(1);

    std::cout << r.sum();

    std::cout << std::endl << std::endl;

    return;

}



Eigen::VectorXd MeritFunction::setInitialPosition(){

    Eigen::VectorXd position = Eigen::VectorXd::Random(fDimension);

    return position;

}


MeritFunction::MeritFunction(){



}
