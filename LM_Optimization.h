#ifndef LM_OPTIMIZATION_H_INCLUDED
#define LM_OPTIMIZATION_H_INCLUDED

#include "MeritFunction.h"
#include <fstream>

class LM_Optimization{

    public:

        LM_Optimization(double maxStepSize,double tolerance);
        double minimize();

    private:

        MeritFunction meritFunction;

        Eigen::VectorXd position;
        Eigen::VectorXd r;
        Eigen::MatrixXd J;

        void evaluateJacobian();
        void dogleg(Eigen::VectorXd& pk);

        double findMaxTau(Eigen::VectorXd& pck, Eigen::VectorXd& pjk);

        double eps,Dbar,D,tol;

};

#endif // LM_OPTIMIZATION_H_INCLUDED
