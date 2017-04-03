// File: Matrix.h
// Author: Rionaldi Chandraseta - 13515077
// Written on 2017-03-31

#ifndef MATRIX_H
#define MATRIX_H

#define INF -1

#include <fstream>
#include <iostream>
#include <string>

class Matrix {
  public:
    Matrix();
    Matrix(std::string FileName);
    Matrix(const Matrix& M);
    ~Matrix();
    Matrix& operator=(const Matrix& M);
    int getDist(int ori, int dest);
    void setDist(int ori, int dest, int dist);
    int getSize();
    void write();

  protected:
    int** Mem;
    int MSize;
};

#endif