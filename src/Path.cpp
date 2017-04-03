// File: Path.cpp
// Author: Rionaldi Chandraseta - 13515077
// Written on 2017-03-31

#include "Path.h"

Path::Path() {
  TotalCost = 0;
}

Path::Path(const Path& P) {
  for (int i=0; i<P.TravelPath.size(); i++) {
    TravelPath.push_back(P.TravelPath.at(i));
  }
  TotalCost = P.TotalCost;
}

void Path::addNode(int nodeNum, int totalCost) {
  TravelPath.push_back(nodeNum);
  TotalCost = totalCost;
}

std::vector<int> Path::getPath() const {
  return TravelPath;
}

int Path::getTotalCost() const {
  return TotalCost;
}
