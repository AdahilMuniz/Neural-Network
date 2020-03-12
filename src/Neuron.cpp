#include "Neuron.h"


Neuron::Neuron(unsigned numOutputs, unsigned _index){
    for (int i = 0; i < numOutputs; ++i){
        connections.push_back(Connection());
        connections[i].weight = randomWeight();
    }

    index = _index;
}

Neuron::~Neuron(){
    //
}

void Neuron::feedForward(const Layer &previousLayer){
    double sum = 0;

    //input*w+b
    for (unsigned i = 0; i < previousLayer.size(); ++i){
        sum += previousLayer[i].getOutput() * previousLayer[i].connections[index].weight;
    }

    //Applying transfer function
    output = Neuron::transferFunction(sum);
}

void Neuron::calcOutputGradients(double target){
    //Gradient = Delta * df(x)
    gradient = (target - output) * Neuron::transferFunctionDerivative(output);
}

void Neuron::calcHiddenGradients(const Layer &nextlayer){
    double sum = 0.0; //Sum of the errors contributions from the next layer

    for (unsigned i = 0; i < nextlayer.size()-1; ++i){
        sum += connections[i].weight * nextlayer[i].gradient;
    }

    //Gradient = Delta * df(x)
    gradient = sum * Neuron::transferFunctionDerivative(output);
}

void Neuron::updateWeights(Layer &prevlayer){

    for (unsigned i = 0; i < prevlayer.size(); ++i){
        double oldDeltaWeight = prevlayer[i].connections[index].deltaWeight;
        double newDeltaWeight = eta * prevlayer[i].getOutput() * gradient + (alpha * oldDeltaWeight);
        
        prevlayer[i].connections[index].deltaWeight = newDeltaWeight;
        prevlayer[i].connections[index].weight += newDeltaWeight;
    }

}