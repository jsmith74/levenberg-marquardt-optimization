#include "LM_Optimization.h"

int main(){

    LM_Optimization optimizer(4.0, 1e-6 );

    optimizer.minimize();

    return 0;

}
