#define DEBUG 0

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
    Matrix * mdelta_weight; //@TODO: Implement momentum

    bool isOutput;
    bool isInput;

    unsigned n;
    unsigned prevLayerN;

    unsigned id;


    Layer(const unsigned &_n, const unsigned &_prevLayerN, const unsigned &_id, const bool &_isOutput = false, const bool &_isInput = false);
    ~Layer();
    
    void forward(Matrix min);
    void backward(Matrix mtarget, Layer * nextLayer);
    void updateWeights(Matrix min, const double &eta);
    void randomWeight();
    
    static double transferFunction(double x) { return NeuralMath::hipTan(x); } //Compiler, do your magic.
    static double transferFunctionDerivative(double x) { return NeuralMath::hipTanDerivative(x); } //Compiler, do your magic.
    
};