#include "NeuralNetwork.h"
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char const **argv){
    ifstream infile(argv[1]);

    double a, b, c;

    vector<unsigned> topology;
    topology.push_back(2);
    topology.push_back(4);
    topology.push_back(1);

    NeuralNetwork net(topology);

    vector<double> inputVals, targetValues, resultValues;


    //Taainning data
    while(infile >> a >> b >> c){
        inputVals.clear();
        targetValues.clear();
        resultValues.clear();

        inputVals.push_back(a);
        inputVals.push_back(b);
    
        net.feedForward(inputVals);
    
        targetValues.push_back(c);
    
        net.backProp(targetValues);
    
        net.getResults(resultValues);

        cout << "Inputs : " << a << " " << b << endl;
        cout << "Result:" << resultValues.back() << endl;
    }

    return 0;
}