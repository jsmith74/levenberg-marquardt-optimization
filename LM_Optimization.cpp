#include "LM_Optimization.h"

#define MACHINEPRECISION 1.1e-16

LM_Optimization::LM_Optimization(){

    meritFunction.setMeritFunction(1);

    J.resize(meritFunction.rDimension,meritFunction.fDimension);

    eps = sqrt(MACHINEPRECISION);

}

void LM_Optimization::evaluateJacobian(){

    for(int i=0;i<meritFunction.fDimension;i++){

        position(i) += eps;

        meritFunction.updateR(position);

        J.col(i) = meritFunction.r;

        position(i) -= eps;

    }

    meritFunction.updateR(position);

    for(int i=0;i<meritFunction.fDimension;i++){

        J.col(i) -= meritFunction.r;

    }

    J /= eps;

    return;

}

double LM_Optimization::minimize(){

    position = meritFunction.setInitialPosition();

    while(true){

        evaluateJacobian();

        break;

    }

    return 2.0;

}
