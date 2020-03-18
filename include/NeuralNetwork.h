#pragma once

#include "Neuron.h"

#include <vector>
#include <iostream>
#include <cassert>
using namespace std;

class NeuralNetwork {

private:
    vector<Layer> layers;
    double error;

public:
    NeuralNetwork(const vector<unsigned> &topology);
    //NeuralNetwork();
    ~NeuralNetwork();
    
    void feedForward(const vector<double> &inputs);
    void backProp   (const vector<double> &targets);
    void getResults (vector<double> &result) const;

};