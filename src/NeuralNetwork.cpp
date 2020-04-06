#include "NeuralNetwork.h"

NeuralNetwork::NeuralNetwork(const vector<unsigned> &topology){
    unsigned numNeuronOutputs = 0;

    layers.push_back(Layer(topology[0], 0, false, true)); //Input Layer
    
    for (unsigned i = 1; i < topology.size(); ++i){
        if (i == topology.size()-1){
            layers.push_back(Layer(topology[i], topology[i-1], true, false)); // Output Layer
        }
        else{
            layers.push_back(Layer(topology[i], topology[i-1], false, false)); // Hidden Layers
        }
    }
}

NeuralNetwork::~NeuralNetwork(){
    //
}

void NeuralNetwork::feedForward(Matrix * min){
    Matrix a = *min;
    //Assert that the number of inputs is equal to the number of neurons from the input layer
    assert(min->nbc == layers[0].n);

    for (unsigned i = 0; i < layers.size(); ++i){
        layers[i].forward(a);
        a = *(layers[i].mout);
    }

    //Set the output from the input layer neurons
    /*
    for (unsigned i = 0; i < inputs.size(); ++i){
        layers[0][i].setOutput(inputs[i]);
    }

    //Foward Propagate
    for (unsigned i = 1; i < layers.size(); ++i){
        Layer &prevLayer = layers[i-1];
        for (unsigned j = 0; j < layers[i].size(); ++j){
            layers[i][j].feedForward(prevLayer);
        }
    }*/
}

void NeuralNetwork::backProp(Matrix * min, Matrix * mtarget){
    Matrix a = *min;
    Matrix y = *mtarget;

    assert(min->nbc == layers[0].n);

    for (unsigned i = 0; i < layers.size(); ++i){
        layers[i].forward(a);
        a = *(layers[i].mout);
    }

    layers.back().backward(y, nullptr); //Output layer

    //Hidden Layers
    for (unsigned i = layers.size() -2; i > 0; --i){
        layers[i].backward(y, &layers[i+1]);
    }

    //Update Weights
    a = *min;
    for (unsigned i = 0; i < layers.size(); ++i){
        layers[i].updateWeights(a, eta);
        a = *(layers[i].mout);
    }

    /*
    error = 0.0;
    Layer &outputLayer = layers.back();
    //Calculate RMS
    for (unsigned i = 0; i < outputLayer.size()-1; ++i){
        double delta = targets[i] - outputLayer[i].getOutput();
        error = delta * delta; 
    }
    error /= outputLayer.size() - 1;
    error = sqrt(error);

    //Implement recent average (?)

    //Calculate output layer gradients
    for (unsigned i = 0; i < outputLayer.size()-1; ++i){
        outputLayer[i].calcOutputGradients(targets[i]);
    }

    //Calculate hidden layers gradients
    for (unsigned i = layers.size() -2; i > 0; --i){
        Layer &hiddenLayer = layers[i];
        Layer &nextLayer = layers[i+1];

        for (unsigned i = 0; i < hiddenLayer.size(); ++i){
            hiddenLayer[i].calcHiddenGradients(nextLayer);
        }
    }

    //Update weights
    for (unsigned i = layers.size() -1; i > 0; --i){
        Layer &layer = layers[i];
        Layer &previousLayer = layers[i-1];
        
        for (unsigned i = 0; i < layer.size() -1 ; ++i){
            layer[i].updateWeights(previousLayer);
        }
    }*/


}

Matrix * NeuralNetwork::getResults() const{
    //layers.back().mout->print();
    return layers.back().mout;
}