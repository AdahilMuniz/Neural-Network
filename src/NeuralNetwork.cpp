#include "NeuralNetwork.h"

NeuralNetwork::NeuralNetwork(const vector<unsigned> &topology){
    
    unsigned numNeuronOutputs = 0;

    for (unsigned i = 0; i < topology.size(); ++i){
        layers.push_back(Layer()); // Create Layers

        //Determine the output number of each neuron on the ith layer.
        if (i == topology.size()-1){//ith layer is the last one.
            numNeuronOutputs = 0;
        }
        else {
            numNeuronOutputs = topology[i+1];
        }

        //Insert Neurons
        for (unsigned j = 0; j <= topology[i]; ++j){
            layers.back().push_back(Neuron(numNeuronOutputs, j));
            //cout << "Neuron Made!" << endl;
        }

        layers.back().back().setOutput(1.0);
    }
}

NeuralNetwork::~NeuralNetwork(){
    //
}


void NeuralNetwork::feedForward(const vector<double> &inputs){
    //Assert that the number of inputs is equal to the number of neurons from the input layer
    //cout << "Input Size: " << inputs.size() << " | Input Layer Size: " << layers[0].size() << endl;
    assert(inputs.size() == (layers[0].size()-1));

    //Set the output from the input layer neurons
    for (unsigned i = 0; i < inputs.size(); ++i){
        layers[0][i].setOutput(inputs[i]);
    }

    //Foward Propagate
    for (unsigned i = 1; i < layers.size(); ++i){
        Layer &prevLayer = layers[i-1];
        for (unsigned j = 0; j < layers[i].size(); ++j){
            layers[i][j].feedForward(prevLayer);
        }
    }
}

void NeuralNetwork::backProp(const vector<double> &targets){
    
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
    }


}

void NeuralNetwork::getResults(vector<double> &result) const{
    result.clear();

    for (unsigned i = 0; i < layers.back().size()-1; ++i){
        result.push_back(layers.back()[i].getOutput());
    }
}