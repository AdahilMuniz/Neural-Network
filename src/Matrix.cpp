#include "Matrix.h"

Matrix::Matrix(int _nbr, int _nbc, double * _values){
    nbr    = _nbr;
    nbc    = _nbc;
    values = _values;
}

Matrix::Matrix(int _nbr, int _nbc, char cont){
    nbr    = _nbr;
    nbc    = _nbc;
    values = new (nothrow) double [nbr*nbc]; 

    if (cont == '1'){
        for (int i = 0; i < nbr*nbc ; ++i){
            values[i] = 1;
        }
    }
}

Matrix::Matrix(){
    //
}

Matrix::~Matrix(){
    //
}

void Matrix::setDim(int _nbr, int _nbc){
    nbr    = _nbr;
    nbc    = _nbc;
    values = new (nothrow) double [nbr*nbc];
}

void Matrix::getDim(int * dim){
    cout << "NBR: " << nbr << endl;
    dim[0] = nbr;
    dim[1] = nbc;
}

Matrix Matrix::operator * (Matrix const &mop){
    Matrix * mr;// = new Matrix();
    int n,m,p;

    if (nbc != mop.nbr){
        return *mr;
    }
    mr = new Matrix(nbr, mop.nbc);

    m = nbr;
    p = mop.nbc;
    n = nbc;
    
    #pragma omp for
    for (int i = 0; i < m; ++i){
        for (int j = 0; j < p; ++j){
            for (int k = 0; k < n; ++k){
                mr->values[p*i + j] += values[i*n + k]*mop.values[k*p + j];
            }
        }
    }
    return * mr;
}

Matrix Matrix::operator * (double const &a){
    Matrix mr(nbr, nbc);

    #pragma omp for
    for (int i = 0; i < nbr * nbc; ++i){
        mr.values[i] = values[i]*a;
    }

    return mr;

}


Matrix Matrix::operator - (Matrix const &mop){
    Matrix mr(nbr, nbc);

    if (nbr != mop.nbr || nbc != mop.nbc){
        return mr;
    }

    #pragma omp for
    for (int i = 0; i < nbr * nbc; ++i){
        mr.values[i] = values[i]-mop.values[i];
    }

    return mr;
}



Matrix Matrix::operator - (double const &a){
    Matrix mr(nbr, nbc);
    
    #pragma omp for
    for (int i = 0; i < nbr * nbc; ++i){
        mr.values[i] = values[i]-a;
    }

    return mr;
}

Matrix Matrix::operator + (Matrix const &mop){
    Matrix mr(nbr, nbc);
    double * result = new (nothrow) double [nbr * nbc];

    if (nbr != mop.nbr || nbc != mop.nbc){
        return mr;
    }
    
    #pragma omp for
    for (int i = 0; i < nbr * nbc; ++i){
        result[i] = values[i]+mop.values[i];
    }
    mr.setValues(result);

    //printf("Time to multiply the matrices A(%dx%d) and B(%dx%d): %f\n", m,n,n,p, omp_get_wtime()-  wall_timer);

    return mr;
}



Matrix Matrix::operator + (double const &a){
    Matrix mr(nbr, nbc);
    double * result = new (nothrow) double [nbr * nbc];
    
    #pragma omp for
    for (int i = 0; i < nbr * nbc; ++i){
        result[i] = values[i]+a;
    }
    mr.setValues(result);

    //printf("Time to multiply the matrices A(%dx%d) and B(%dx%d): %f\n", m,n,n,p, omp_get_wtime()-  wall_timer);

    return mr;
}

Matrix Matrix::point (Matrix const &mop){
    Matrix mr(nbr, nbc);
    double * result = new (nothrow) double [nbr * nbc];

    if (nbr != mop.nbr || nbc != mop.nbc){
        return mr;
    }
    
    #pragma omp for
    for (int i = 0; i < nbr * nbc; ++i){
        mr.values[i] = values[i]*mop.values[i];
    }

    return mr;
}

Matrix Matrix::concatenate(Matrix const &mop, bool axis){
    Matrix * mr;

    if (axis == 0){
        if(mop.nbc != nbc){
            return *mr;
        }

        mr = new Matrix(nbr + mop.nbr, nbc);

        #pragma omp for
        for (int i = 0; i < nbc*nbr; ++i){
            mr->values[i] = values[i];
        }
        #pragma omp for
        for (int i = 0; i < mop.nbc*mop.nbr; ++i){
            mr->values[i+nbc*nbr] = mop.values[i];
        }
    }
    else{
        if(mop.nbr != nbr){
            return *mr;
        }

        mr = new Matrix(nbr, nbc + mop.nbc);

        #pragma omp for
        for (int i = 0; i < nbr; ++i){
            for (int j = 0; j < nbc; ++j){
                mr->values[j+(nbc+mop.nbc)*i] = values[j+nbc*i];
            }
        }
        
        #pragma omp for
        for (int i = 0; i < mop.nbr; ++i){
            for (int j = 0; j < mop.nbc; ++j){
                mr->values[j+nbc+(nbc+mop.nbc)*i] = mop.values[j+mop.nbc*i];
            }
        }
    }
    return *mr;
}

Matrix Matrix::concatenate(Matrix * mop, bool axis){
    Matrix * mr;

    if (axis == 0){
        if(mop->nbc != nbc){
            return *mr;
        }

        mr = new Matrix(nbr + mop->nbr, nbc);

        #pragma omp for
        for (int i = 0; i < nbc*nbr; ++i){
            mr->values[i] = values[i];
        }
        #pragma omp for
        for (int i = 0; i < mop->nbc*mop->nbr; ++i){
            mr->values[i+nbc*nbr] = mop->values[i];
        }
    }
    else{
        if(mop->nbr != nbr){
            return *mr;
        }

        mr = new Matrix(nbr, nbc + mop->nbc);

        #pragma omp for
        for (int i = 0; i < nbr; ++i){
            for (int j = 0; j < nbc; ++j){
                mr->values[j+(nbc+mop->nbc)*i] = values[j+nbc*i];
            }
        }
        
        #pragma omp for
        for (int i = 0; i < mop->nbr; ++i){
            for (int j = 0; j < mop->nbc; ++j){
                mr->values[j+nbc+(nbc+mop->nbc)*i] = mop->values[j+mop->nbc*i];
            }
        }
    }
    return *mr;
}


Matrix Matrix::transpose(){
    Matrix mr(nbc, nbr);

    #pragma omp for
    for (int i = 0; i < nbr; ++i){
        for (int j = 0; j < nbc; ++j){
            mr.values[i + j*nbr] = values[j + i*nbc];
        }
    }
    return mr;
}

void Matrix::print(){
    for (int i = 0; i < nbr; ++i){
        for (int j = 0; j < nbc; ++j){
            cout << values[j + i*nbc] << " ";
        }
        cout <<"\n";
    }
}