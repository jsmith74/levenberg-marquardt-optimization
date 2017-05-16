#include "MeritFunction.h"



void MeritFunction::setMeritFunction(int intParam){

    fDimension = 2;

    rDimension = 2;

    return;

}

void MeritFunction::updateR(Eigen::VectorXd& position,Eigen::VectorXd& r){

    r(0) = position(0);
    r(1) = 10*position(0)/(position(0) + 0.1) + 2*position(1)*position(1);

    /** ALSO TRY PLUGGING IN SQUARES OF THIS ============= */

    return;

}



void MeritFunction::printReport(Eigen::VectorXd& position){

    Eigen::VectorXd r(2);

    r(0) = position(0);
    r(1) = 10*position(0)/(position(0) + 0.1) + 2*position(1)*position(1);

    std::cout << r.transpose();

    return;

}



Eigen::VectorXd MeritFunction::setInitialPosition(){

    Eigen::VectorXd position = Eigen::VectorXd::Random(fDimension);

    return position;

}


MeritFunction::MeritFunction(){



}
