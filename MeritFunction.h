#ifndef MERITFUNCTION_H_INCLUDED
#define MERITFUNCTION_H_INCLUDED

#include <Eigen/Dense>
#include <iostream>

class MeritFunction{

    public:

        MeritFunction();
        void setMeritFunction(int intParam);
        void updateR(Eigen::VectorXd& position,Eigen::VectorXd& r);
        int fDimension,rDimension;
        void printReport(Eigen::VectorXd& position);
        Eigen::VectorXd setInitialPosition();

    private:



};

#endif // MERITFUNCTION_H_INCLUDED
