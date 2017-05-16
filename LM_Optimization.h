#ifndef LM_OPTIMIZATION_H_INCLUDED
#define LM_OPTIMIZATION_H_INCLUDED

#include "MeritFunction.h"

class LM_Optimization{

    public:

        LM_Optimization();
        double minimize();

    private:

        MeritFunction meritFunction;

        Eigen::VectorXd position;
        Eigen::MatrixXd J;

        void evaluateJacobian();

        double eps;

};

#endif // LM_OPTIMIZATION_H_INCLUDED
