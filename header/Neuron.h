#pragma once

#include "NeuralMath.h"

#include <vector>
#include <iostream>
#include <cstdlib>
using namespace std;

class Neuron;

typedef struct connection {
    double weight;
    double deltaWeight;
    
} Connection;

typedef vector<Neuron> Layer;


class Neuron
{
private:
    unsigned index;
    double output;
    double gradient;
    double eta = 0.15; // Learning Rate
    double alpha = 0.5; // Momentum (?)
    vector<Connection> connections;

public:
    Neuron(unsigned numOutputs, unsigned _index);
    ~Neuron();

    void   setOutput(double val) { output = val; }
    double getOutput() const { return output; }
    void   feedForward(const Layer &previousLayer);
    void   calcOutputGradients(double target);
    void   calcHiddenGradients(const Layer &nextlayer);
    void   updateWeights(Layer &prevlayer);


    static double randomWeight(void) { return rand()/double(RAND_MAX); }
    static double transferFunction(double x) { return NeuralMath::hipTan(x); } //Compiler, do your magic.
    static double transferFunctionDerivative(double x) { return NeuralMath::hipTanDerivative(x); } //Compiler, do your magic.
    
};