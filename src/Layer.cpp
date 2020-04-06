#include "Layer.h"

Layer::Layer(const int &_n, const int &_prevLayerN, const bool &_isOutput, const bool &_isInput){
    n             = _n; //Number of neurons
    prevLayerN    = _prevLayerN; //Number of neurons on the previous layer

    isOutput      = _isOutput;
    isInput       = _isInput;

    mout          = new Matrix(); //new Matrix(m,n);
    mdz           = new Matrix(); //new Matrix(m,n);
    mdelta        = new Matrix(); //new Matrix(m,n);

    mweight       = new Matrix(prevLayerN,n); // Weight Matrix(PrevLayerN X LayerN)
    mdelta_weight = new Matrix(prevLayerN,n); // Delta Weight Matrix(PrevLayerN X LayerN)
}

Layer::~Layer(){
    //
}

void Layer::forward(Matrix min){

    //mdz  = new Matrix(min.nbr,n);
    //mout = new Matrix(min.nbr,n);
    //mdz ->setDim(min.nbr,n)
    //mout->setDim(min.nbr,n);

    if (!isInput){
        (*mout)  = min*(*mweight);
        (*mdz)   = (*mout);

        //values = mout->getValues();
        for (unsigned i = 0; i < mout->nbr*mout->nbc; ++i){
            mdz ->values[i] = transferFunctionDerivative(mout->values[i]);
            mout->values[i] = transferFunction(mout->values[i]);
        }
    }
    else{
        (*mout) = min;
    }
    //cout << "MOUT - NBR: " << mout->nbr << " NBC: " << mout->nbc << endl;
}

void Layer::backward(Matrix mtarget, Layer * nextLayer){
    if (isOutput){
        *mdelta = ((*mout) - mtarget).point(*mdz);
    }
    else{
        //cout << "MWEIGHT - NBR: " << nextLayer->mweight->nbr << " NBC: " << nextLayer->mweight->nbc << endl;
        //cout << "MDELTA  - NBR: " << nextLayer->mdelta->nbr << " NBC: " << nextLayer->mdelta->nbc << endl;
        *mdelta = ((*(nextLayer->mdelta)) * nextLayer->mweight->transpose()).point(*mdz);
        //cout << "oi" << endl;
    }
}

void Layer::updateWeights(Matrix min, const double &eta){
    *mweight = (min.transpose() * (*mdelta))*eta;
}
