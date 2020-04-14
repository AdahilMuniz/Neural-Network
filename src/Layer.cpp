#include "Layer.h"

Layer::Layer(const unsigned &_n, const unsigned &_prevLayerN, const unsigned &_id, const bool &_isOutput, const bool &_isInput){
    n             = _n; //Number of neurons
    prevLayerN    = _prevLayerN; //Number of neurons on the previous layer

    isOutput      = _isOutput;
    isInput       = _isInput;

    id            = _id;

    mout          = new Matrix(); //new Matrix(m,n);
    mdz           = new Matrix(); //new Matrix(m,n);
    mdelta        = new Matrix(); //new Matrix(m,n);

    mweight       = new Matrix(prevLayerN,n, '1'); // Weight Matrix(PrevLayerN X LayerN)
    mdelta_weight = new Matrix(prevLayerN,n); // Delta Weight Matrix(PrevLayerN X LayerN)

    randomWeight();

}

Layer::~Layer(){
    //
}

void Layer::randomWeight(){
    for (unsigned i = 0; i < mweight->nbr; ++i){
        for (unsigned j = 0; j < mweight->nbc; ++j){
            mweight->values[j + i*mweight->nbc] = rand()/double(RAND_MAX); 
        }
    }
}

void Layer::forward(Matrix min){

    if (!isInput){
        (*mout)  = min*(*mweight);
        mdz   = new Matrix(mout->nbr, mout->nbc);//(*mout);

        for (unsigned i = 0; i < mout->nbr*mout->nbc; ++i){
            mdz ->values[i] = transferFunctionDerivative(mout->values[i]);  
            mout->values[i] = transferFunction(mout->values[i]);
        }
    }
    else{
        (*mout) = min;
    }
    
#if DEBUG == 1

    cout << "ID: " << id << endl;
    cout << "MOUT: " << endl;
    mout->print();
    cout << "------------------------" << endl; 

    cout << "ID: " << id << endl;
    cout << "DZ: " << endl;
    mdz->print();
    cout << "------------------------" << endl;
    
#endif
}

void Layer::backward(Matrix mtarget, Layer * nextLayer){
    if (isOutput){
        *mdelta = ((*mout) - mtarget).point(*mdz);
    }
    else{
        *mdelta = ((*(nextLayer->mdelta)) * nextLayer->mweight->transpose()).point(*mdz);
    }

#if DEBUG == 1

    cout << "ID: " << id << endl;
    cout << "TARGET: " << endl;
    mtarget.print();
    cout << "------------------------" << endl;

    cout << "ID: " << id << endl;
    cout << "OUT: " << endl;
    mout->print();
    cout << "------------------------" << endl;
    
    cout << "ID: " << id << endl;
    cout << "DZ: " << endl;
    mdz->print();
    cout << "------------------------" << endl;

    cout << "ID: " << id << endl;
    cout << "DELTA: " << endl;
    mdelta->print();
    cout << "------------------------" << endl;
    

#endif

}

void Layer::updateWeights(Matrix min, const double &eta){
#if DEBUG == 1
    cout << "ID: " << id << endl;
    cout << "WEIGHT(BEFORE) : " << endl;
    mweight->print();
    cout << "------------------------" << endl;
#endif

    *mweight = (*mweight) - (min.transpose() * (*mdelta))*eta;

#if DEBUG == 1

    cout << "ID: " << id << endl;
    cout << "WEIGHT(AFTER): " << endl;
    mweight->print();
    cout << "------------------------" << endl;

    cout << "ID: " << id << endl;
    cout << "DELTA: " << endl;
    mdelta->print();
    cout << "------------------------" << endl;

    cout << "ID: " << id << endl;
    cout << "MIN TRANSPOSE: " << endl;
    min.transpose().print();
    cout << "------------------------" << endl;

#endif
}
