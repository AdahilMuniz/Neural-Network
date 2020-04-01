#include <iostream>
#include <omp.h>
#include <vector>
#include <new>

using namespace std;

//typedef vector<vector<double>> MatrixArray;

class Matrix
{
private:
    double * values;
    int nbr, nbc;

public:
    Matrix(int _nbr, int _nbc, double * _values);
    Matrix(double * _values);
    Matrix();
    Matrix(int _nbr, int _nbc);
    ~Matrix();

    void setValues(double * _values){ values = _values; };
    void setDim(int _nbr, int _nbc);

    void print();

    Matrix operator * (Matrix const &mop);
    Matrix operator * (double const &op);
    Matrix operator - (Matrix const &mop);
    Matrix operator - (double const &op);
    Matrix operator + (Matrix const &mop);
    Matrix operator + (double const &op);


    void   transpose();
    
};


/*
int main(int argc, char const *argv[])
{

    double m_val [][3] = {{1.0,2.0,3.0},
                     {4.0,5.0,6.0},
                     {7.0,8.0,9.0},
                     {7.0,8.0,9.0}};

    Matrix m1(4,3,(double *) m_val);
    Matrix m2(3,3,(double *) m_val);
    Matrix m3;

    m3 = m1*m2;
    m3 = m1+3;

    m3.print();

    m3.transpose();
    cout << "\n";
    m3.print();

    return 0;
}*/