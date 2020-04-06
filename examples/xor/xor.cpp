
#include "Matrix.h"
#include "NeuralNetwork.h"
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char const **argv){
    ifstream infile_train(argv[1]);
    ifstream infile_test (argv[2]);

    double a, b, c;

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

        //inputVals.clear();
        //targetValues.clear();

        inputVals.push_back(a);
        inputVals.push_back(b);
        targetValues.push_back(c);
    
        /*
        net.backProp(targetValues);
    
        net.getResults(resultValues);

        cout << "Inputs : " << a << " " << b << endl;
        cout << "Result:" << resultValues.back() << endl;
        */
    }

    min     = new Matrix(inputVals.size()/2,2, &inputVals[0]);
    mtarget = new Matrix(targetValues.size()/1,1, &targetValues[0]);

    net.backProp(min, mtarget);
    
    inputVals.clear();
    targetValues.clear();

    //Test data
    while(infile_test >> a >> b >> c){

        inputVals.push_back(a);
        inputVals.push_back(b);
        targetValues.push_back(c);
    }

    mintest = new Matrix(inputVals.size()/2,2, &inputVals[0]);

    mintest->print();

    net.feedForward(mintest);
    mresult = net.getResults();

    mresult->print();

    cout << "DIM: " << mresult->nbr << " X " << mresult->nbc <<endl; ;

    return 0;
}