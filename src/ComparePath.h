// File: ComparePath.h
// Author: Rionaldi Chandraseta - 13515077
// Written on 2017-04-01

#ifndef COMPAREPATH_H
#define COMPAREPATH_H

#include "Path.h"

class ComparePath {
  public:
    bool operator() (Path& P1, Path& P2) {
      return P1.getTotalCost() > P2.getTotalCost();
    }
};

#endif