#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <omp.h>
#include <vector>
#include <new>

using namespace std;

//typedef vector<vector<double>> MatrixArray;

class Matrix
{
private:

public:

    double * values;
    int nbr, nbc;

    Matrix(int _nbr, int _nbc, double * _values);
    Matrix(double * _values);
    Matrix();
    Matrix(int _nbr, int _nbc, char cont = '0');
    ~Matrix();

    void setValues(double * _values){ values = _values; };
    void setDim(int _nbr, int _nbc);

    double * getValues() const { return values; }
    void    getDim(int * dim);

    void print();

    Matrix operator * (Matrix const &mop);
    Matrix operator * (double const &op);
    Matrix operator - (Matrix const &mop);
    Matrix operator - (double const &op);
    Matrix operator + (Matrix const &mop);
    Matrix operator + (double const &op);

    Matrix concatenate(Matrix const &mop, bool axis = 0);
    Matrix concatenate(Matrix *mop, bool axis = 0);

    Matrix point(Matrix const &mop);
    Matrix transpose();
    
};

#endif