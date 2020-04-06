#include "NeuralMath.h"
#include "Matrix.h"

class Layer{

private:

public:
    Matrix * mout;
    Matrix * min;
    Matrix * mdz;
    Matrix * mdelta;
    Matrix * mweight;
    Matrix * mdelta_weight;

    bool isOutput;
    bool isInput;

    int n;
    int prevLayerN;


    Layer(const int &_n, const int &_prevLayerN, const bool &_isOutput = false, const bool &_isInput = false);
    ~Layer();
    
    void forward(Matrix min);
    void backward(Matrix mtarget, Layer * nextLayer);
    void updateWeights(Matrix min, const double &eta);

    static double transferFunction(double x) { return NeuralMath::hipTan(x); } //Compiler, do your magic.
    static double transferFunctionDerivative(double x) { return NeuralMath::hipTanDerivative(x); } //Compiler, do your magic.
    
};

/*
int main(int argc, char const *argv[])
{
    
    return 0;
}
*/