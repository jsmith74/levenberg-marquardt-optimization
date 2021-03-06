#include "LM_Optimization.h"

#define MACHINEPRECISION 1.1e-16

#define ETA 0

/** ===== Print Step Monitor ======================================= */

#define PRINT_STEP_MONITOR

/** ================================================================ */

/** ===== Seed Random Number Generator ============================= */

#define SEED_RANDOM_NUMBER_GENERATOR

/** ================================================================ */

/** ===== Turn Experimental Stopping Condition On ================== */

#define USE_EXPERIMENTAL_STOPPING_CONDITION

/** ================================================================ */

/** ===== Set Maximum number of steps algorithm will take ========== */

#define MAXIMUM_NUMBER_OF_STEPS 6000

/** ================================================================ */

LM_Optimization::LM_Optimization(double maxStepSize,double tolerance){

    #ifdef SEED_RANDOM_NUMBER_GENERATOR

        srand(611*time(NULL));

    #endif // SEED_RANDOM_NUMBER_GENERATOR

    meritFunction.setMeritFunction();

    J.resize(meritFunction.rDimension,meritFunction.fDimension);

    r.resize(meritFunction.rDimension);

    eps = sqrt(MACHINEPRECISION);

    Dbar = maxStepSize;

    tol = tolerance;

}

void LM_Optimization::evaluateJacobian(){

    for(int i=0;i<meritFunction.fDimension;i++){

        position(i) += eps;

        meritFunction.updateR(position,r);

        J.col(i) = r;

        position(i) -= eps;

    }

    meritFunction.updateR(position,r);

    for(int i=0;i<meritFunction.fDimension;i++){

        J.col(i) -= r;

    }

    J /= eps;

    return;

}

double LM_Optimization::findMaxTau(Eigen::VectorXd& pck, Eigen::VectorXd& pjk){

    double output1,output2;

    output1 = pck.norm();

    if(output1 > D) return 0.0;


    for(double tau=0.0;tau<=1.0;tau+=0.0001){

        output2 = ( pck + tau * (pjk - pck) ).norm();

        if(output1 > output2){

            printTau(pck,pjk);

            //assert(output2 >= output1);

        }

        if( output2 > D ){

            assert( output1 <= D );

            return tau - 0.0001;

        }

        output1 = output2;

    }

    return 1.0;

}

void LM_Optimization::printTau(Eigen::VectorXd& pck, Eigen::VectorXd& pjk){

    std::ofstream outfile("test.dat");

    for(double tau=0.0;tau<=1.0;tau+=0.0001){

        outfile << tau << "\t" << ( pck + tau * (pjk - pck) ).norm() << "\t" << D  <<std::endl;

    }

    outfile.close();

    return;

}

void LM_Optimization::dogleg(Eigen::VectorXd& pk){

    double tau = std::min(1.0 , pow( ( J.transpose() * r ).norm() , 3) / ( D * r.transpose() * J * J.transpose() * J * J.transpose() * r ) );

    Eigen::VectorXd pck = -tau * ( D/( ( J.transpose() * r ).norm() ) ) * J.transpose() * r;

    if( pck.norm() == D ) pk = pck;

    else{

         Eigen::VectorXd pjk = -( J.transpose() * J ).inverse() * ( J.transpose() * r );//-J.inverse() * r;

         double tauSub = findMaxTau(pck,pjk);

         pk = pck + tauSub * (pjk - pck);

    }

    return;

}

double LM_Optimization::minimize(){

    position = meritFunction.setInitialPosition();

    D = Dbar * (1.0*rand() / RAND_MAX);

    Eigen::VectorXd pk;

    int stepIndex = 0;

    while(true){

        evaluateJacobian();

        #ifdef PRINT_STEP_MONITOR

            std::cout << stepIndex << "\t" << r.sum() << "\t";

        #endif // PRINT_STEP_MONITOR

        #ifdef USE_EXPERIMENTAL_STOPPING_CONDITION

            if( D < tol) break;

        #endif // USE_EXPERIMENTAL_STOPPING_CONDITION

        if( stepIndex > MAXIMUM_NUMBER_OF_STEPS ) break;

        stepIndex++;

        dogleg(pk);

        double rhoDenom = r.transpose() * r;

        rhoDenom -= ( r + J * pk ).transpose() * ( r + J * pk );

        double rho = ( r.transpose() * r );

        Eigen::VectorXd tempPosition = position + pk;

        meritFunction.updateR(tempPosition,r);

        rho -= r.transpose() * r;

        if(rhoDenom != 0) rho /= rhoDenom;

        #ifdef PRINT_STEP_MONITOR

            std::cout << rho << "\t" << D << std::endl; //"\t" << J.determinant()  << std::endl;

        #endif // PRINT_STEP_MONITOR

        if(rho < 0.25) D = 0.25 * pk.norm();

        else{

            if(rho > 0.75 && pk.norm() == D) D = std::min(2*D,Dbar);

        }

        if( rho > ETA ) position += pk;


    }

    meritFunction.printResult(position,r);

    return 2.0;

}
