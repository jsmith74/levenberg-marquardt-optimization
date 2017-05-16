#ifndef MERITFUNCTION_H_INCLUDED
#define MERITFUNCTION_H_INCLUDED

#include <Eigen/Dense>
#include <iostream>

class MeritFunction{

    public:

        MeritFunction();
        void setMeritFunction(int intParam);
        double f();
        void updateR(Eigen::VectorXd& position);
        int fDimension,rDimension;
        void printReport(Eigen::VectorXd& position);
        Eigen::VectorXd setInitialPosition();
        Eigen::VectorXd r;

    private:



};

#endif // MERITFUNCTION_H_INCLUDED
