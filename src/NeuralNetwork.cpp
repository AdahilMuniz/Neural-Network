#include "NeuralNetwork.h"

NeuralNetwork::NeuralNetwork(const vector<unsigned> &topology){
    unsigned numNeuronOutputs = 0;

    layers.push_back(Layer(topology[0]+1, 0, 0, false, true)); //Input Layer
    
    for (unsigned i = 1; i < topology.size(); ++i){
        if (i == topology.size()-1){
            layers.push_back(Layer(topology[i], topology[i-1]+1, i, true, false)); // Output Layer
        }
        else{
            layers.push_back(Layer(topology[i]+1, topology[i-1]+1, i, false, false)); // Hidden Layers
        }
    }
}

NeuralNetwork::~NeuralNetwork(){
    //
}

void NeuralNetwork::feedForward(Matrix * min){
    Matrix a = min->concatenate(new Matrix(min->nbr, 1, '1'), 1);

    assert(a.nbc == layers[0].n);

    for (unsigned i = 0; i < layers.size(); ++i){
        layers[i].forward(a);
        a = *(layers[i].mout);
    }

}

void NeuralNetwork::backProp(Matrix * min, Matrix * mtarget, const unsigned &epoch){

    Matrix a;
    Matrix * y;

    for (unsigned i = 0; i < epoch; ++i)
    {
        
        a = min->concatenate(new Matrix(min->nbr, 1, '1'), 1);
        y = mtarget;
    
        assert(a.nbc == layers[0].n);
        
        for (unsigned i = 0; i < layers.size(); ++i){
            layers[i].forward(a);
            a = *(layers[i].mout);
        }

        layers.back().backward(*mtarget, nullptr); //Output layer

        //Hidden Layers
        for (unsigned i = layers.size() -2; i > 0; --i){
            //cout << "I: " << i << endl;
            layers[i].backward(*mtarget, &layers[i+1]);
        }

        //Update Weights
        a = min->concatenate(new Matrix(min->nbr, 1, '1'), 1);

        for (unsigned i = 1; i < layers.size(); ++i){
            layers[i].updateWeights(a, eta);
            a = *(layers[i].mout);
        }
    }
}

Matrix * NeuralNetwork::getResults() const{
    return layers.back().mout;
}