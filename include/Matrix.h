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
    Matrix(int _nbr, int _nbc);
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

    Matrix point(Matrix const &mop);
    Matrix transpose();
    
};

#endif

/*
int main(int argc, char const *argv[])
{

    double m_val [][3] = {{1.0,2.0,3.0},
                     {4.0,5.0,6.0},
                     {7.0,8.0,9.0},
                     {7.0,8.0,9.0}};

    Matrix m1(4,3,(double *) m_val);
    Matrix m2(3,3,(double *) m_val);
    Matrix * m3;

    m3 = new Matrix();

    *m3 = m1*m2;

    cout << "NBR: " << m3->nbc << " NBC: " << m3->nbr << endl;

    return 0;
}
*/