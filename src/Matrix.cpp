#include "Matrix.h"
#include <stdio.h>

Matrix::Matrix(int _nbr, int _nbc, double * _values){
    nbr    = _nbr;
    nbc    = _nbc;
    values = _values;
}

Matrix::Matrix(int _nbr, int _nbc){
    nbr    = _nbr;
    nbc    = _nbc;
    //values = new (nothrow) double [nbr*nbc]; 
}

Matrix::Matrix(){

}

Matrix::~Matrix(){
    //
}

void Matrix::setDim(int _nbr, int _nbc){
    nbr    = _nbr;
    nbc    = _nbc;
    values = new (nothrow) double [nbr*nbc];
}

Matrix Matrix::operator * (Matrix const &mop){
    Matrix * mr = new Matrix();
    double * result = new (nothrow) double [nbr * mop.nbc];
    int n,m,p;

    if (nbc != mop.nbr){
        return *mr;
    }
    mr = new Matrix(nbr, mop.nbc);

    m = nbr;
    p = mop.nbc;
    n = nbc;
    
    //double wall_timer = omp_get_wtime();
    #pragma omp for
    for (int i = 0; i < m; ++i){
        for (int j = 0; j < p; ++j){
            for (int k = 0; k < n; ++k){
                result[p*i + j] += values[i*n + k]*mop.values[k*p + j];
            }
        }
    }
    mr->setValues(result);

    //printf("Time to multiply the matrices A(%dx%d) and B(%dx%d): %f\n", m,n,n,p, omp_get_wtime()-  wall_timer);

    return * mr;
}

Matrix Matrix::operator * (double const &a){
    Matrix mr(nbr, nbc);
    double * result = new (nothrow) double [nbr * nbc];

    #pragma omp for
    for (int i = 0; i < nbr * nbc; ++i){
        result[i] = values[i]*a;
    }
    mr.setValues(result);

    return mr;

}

Matrix Matrix::operator - (Matrix const &mop){
    Matrix mr(nbr, nbc);
    double * result = new (nothrow) double [nbr * nbc];

    if (nbc != mop.nbr || nbc != mop.nbc){
        return mr;
    }
    
    #pragma omp for
    for (int i = 0; i < nbr * nbc; ++i){
        result[i] = values[i]-mop.values[i];
    }
    mr.setValues(result);

    //printf("Time to multiply the matrices A(%dx%d) and B(%dx%d): %f\n", m,n,n,p, omp_get_wtime()-  wall_timer);

    return mr;
}



Matrix Matrix::operator - (double const &a){
    Matrix mr(nbr, nbc);
    double * result = new (nothrow) double [nbr * nbc];
    
    #pragma omp for
    for (int i = 0; i < nbr * nbc; ++i){
        result[i] = values[i]-a;
    }
    mr.setValues(result);

    //printf("Time to multiply the matrices A(%dx%d) and B(%dx%d): %f\n", m,n,n,p, omp_get_wtime()-  wall_timer);

    return mr;
}

Matrix Matrix::operator + (Matrix const &mop){
    Matrix mr(nbr, nbc);
    double * result = new (nothrow) double [nbr * nbc];

    if (nbc != mop.nbr || nbc != mop.nbc){
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


void Matrix::transpose(){
    double * result = new (nothrow) double [nbr * nbc];

    #pragma omp for
    for (int i = 0; i < nbr; ++i){
        for (int j = 0; j < nbc; ++j){
            result[i + j*nbr] = values[j + i*nbc];
        }
    }
    swap(nbr, nbc);
    values = result;
}

void Matrix::print(){
    //cout << "nbr: " << nbr << endl;
    //cout << "nbc: " << nbc << endl;
    for (int i = 0; i < nbr; ++i){
        for (int j = 0; j < nbc; ++j){
            cout << values[j + i*nbc] << " ";
        }
        cout <<"\n";
    }
}