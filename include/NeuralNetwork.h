#pragma once

#include "Matrix.h"
#include "Layer.h"

#include <vector>
#include <iostream>
#include <cassert>
using namespace std;

class NeuralNetwork {

private:
    vector<Layer> layers;
    double error;
    double eta = 0.01;
public:
    NeuralNetwork(const vector<unsigned> &topology);
    ~NeuralNetwork();
    
    void feedForward(Matrix * min);
    void backProp   (Matrix * min, Matrix * mtarget, const unsigned &epoch = 100);
    Matrix * getResults () const;

};