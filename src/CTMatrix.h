// File: CTMatrix.h
// Author: Rionaldi Chandraseta - 13515077
// Written on 2017-03-31

#include <queue>

#include "ComparePath.h"
#include "Matrix.h"
#include "Path.h"

#ifndef CTMATRIX_H
#define CTMATRIX_H

class CTMatrix {
  public:
    CTMatrix(std::string FileName);
    Matrix getMatrix();
    int getNumCheckedNode();
    double getInitialCost();
    double getCost(int node);
    double getCost(int orig, int dest);
    double getNodesCost(std::vector<int> visited);
    void solve();
    Path getShortestPath();

  private:
    Matrix Dist;
    std::priority_queue<Path, std::vector<Path>, ComparePath> CurrentTravelPath;
    int NumCheckedNode;
};

#endif