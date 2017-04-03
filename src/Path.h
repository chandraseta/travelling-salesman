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
    void addNode(int nodeNum, int totalCost);
    std::vector<int> getPath() const;
    int getTotalCost() const;

  private:
    std::vector<int> TravelPath;
    int TotalCost;
};

#endif