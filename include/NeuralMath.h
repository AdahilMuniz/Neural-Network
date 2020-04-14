#include <math.h>

namespace NeuralMath{
    
    inline double sigmoid(const double &x){
        return 1.0/(1.0+exp(-x));
    }

    inline double sigmoidDerivative(const double &x){
        return sigmoid(x)*(1-sigmoid(x));
    }

    inline double hipTan(const double &x){
        return tanh(x);
    }

    inline double hipTanDerivative(const double &x){
        //return 1.0 - x * x;
        return 1.0 - pow(tanh(x), 2);
    }


}