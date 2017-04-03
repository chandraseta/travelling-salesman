// File: RCMatrix.h
// Author: Rionaldi Chandraseta - 13515077
// Written on 2017-03-31

#include <queue>

#include "ComparePath.h"
#include "Matrix.h"
#include "Path.h"

#ifndef RCMATRIX_H
#define RCMATRIX_H

class RCMatrix {
  public:
    RCMatrix();
    RCMatrix(std::string FileName);
    RCMatrix(const RCMatrix& R);
    RCMatrix createDummy();
    Matrix getMatrix();
    int getBound();
    int getNumCheckedNode();
    int lowestRowDist(int row);
    int lowestColDist(int col);
    void travel(int orig, int dest);
    void reduceMatrix();
    void solve();
    Path getShortestPath();

  private:
    Matrix Dist;
    std::priority_queue<Path, std::vector<Path>, ComparePath> CurrentTravelPath;
    int Bound;
    int NumCheckedNode;
};

#endif