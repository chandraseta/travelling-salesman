// File: Path.h
// Author: Rionaldi Chandraseta - 13515077
// Written on 2017-03-31

#ifndef PATH_H
#define PATH_H

#include <vector>

class Path {
  public:
    Path();
    Path(const Path& P);
    void addNode(int nodeNum, double totalCost);
    std::vector<int> getPath() const;
    double getTotalCost() const;

  private:
    std::vector<int> TravelPath;
    double TotalCost;
};

#endif