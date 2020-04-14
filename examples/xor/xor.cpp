
#include "Matrix.h"
#include "NeuralNetwork.h"
#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

int main(int argc, char const **argv){

    if (argc < 4){
        cout << "Provide enough arguments" << endl;
        return 0;
    }

    ifstream infile_train(argv[1]);
    ifstream infile_test (argv[2]);

    double a, b, c;
    int epoch = atoi(argv[3]);

    vector<unsigned> topology;
    topology.push_back(2);
    topology.push_back(4);
    topology.push_back(1);

    NeuralNetwork net(topology);

    vector<double> inputVals, targetValues, resultValues;
    Matrix * min, *mintest, * mtarget;
    Matrix * mresult;


    //Trainning data
    while(infile_train >> a >> b >> c){

        inputVals.push_back(a);
        inputVals.push_back(b);
        targetValues.push_back(c);
    }

    min     = new Matrix(inputVals.size()/2,2, &inputVals[0]);
    mtarget = new Matrix(targetValues.size()/1,1, &targetValues[0]);

    net.backProp(min, mtarget, epoch);
    
    inputVals.clear();
    targetValues.clear();

    //Test data
    while(infile_test >> a >> b >> c){

        inputVals.push_back(a);
        inputVals.push_back(b);
        targetValues.push_back(c);
    }

    mintest = new Matrix(inputVals.size()/2,2, &inputVals[0]);

    net.feedForward(mintest);
    mresult = net.getResults();

    mresult->print();

    return 0;
}