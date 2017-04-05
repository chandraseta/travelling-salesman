// File: CTMatrix.cpp
// Author: Rionaldi Chandraseta - 13515077
// Written on 2017-04-03

#include <algorithm>

#include "CTMatrix.h"

CTMatrix::CTMatrix(std::string FileName) : Dist(FileName) {
  NumCheckedNode = 1;
}

Matrix CTMatrix::getMatrix() {
  return Dist;
}

int CTMatrix::getNumCheckedNode() {
  return NumCheckedNode;
}

double CTMatrix::getInitialCost() {
  double totalCost = 0;
  int size = Dist.getSize();
  for (int row=1; row<=size; row++) {
    double min = 0x3f3f3f3f;
    double prevMin = 0x3f3f3f3f;
    for (int col=1; col<=size; col++) {
      if (Dist.getDist(row, col) >= 0) {
        if (Dist.getDist(row, col) < min) {
          prevMin = min;
          min = Dist.getDist(row, col);
        }
        else if (Dist.getDist(row, col) < prevMin) {
          prevMin = Dist.getDist(row, col);
        }
      }
    }
    totalCost += (min + prevMin);
  }
  return totalCost*0.5;
}

double CTMatrix::getCost(int orig, int dest) {
  double min = 0x3f3f3f3f;
  int size = Dist.getSize();
  for (int col=1; col<=size; col++) {
    if ((col != dest) && (Dist.getDist(orig, col) >= 0) && (Dist.getDist(orig, col) < min)) {
      min = Dist.getDist(orig, col);
    }
  }
  double cost = min + Dist.getDist(orig, dest);
  return cost;
}

double CTMatrix::getCost(int node) {
  double min = 0x3f3f3f3f;
  double prevMin = 0x3f3f3f3f;
  int size = Dist.getSize();
  for (int col=1; col<=size; col++) {
    if ((col != node) && (Dist.getDist(node, col) >= 0)) {
      if (Dist.getDist(node, col) < min) {
        prevMin = min;
        min = Dist.getDist(node, col);
      }
      else if (Dist.getDist(node, col) < prevMin) {
        prevMin = Dist.getDist(node, col);
      }
    }
  }
  return (min + prevMin);
}

double CTMatrix::getNodesCost(std::vector<int> visited) {
  double totalCost = 0;
  if (visited.size()==1) {
    totalCost = 2*getInitialCost();
  }
  else {
    int size = Dist.getSize();
    int visSize = visited.size();
    for (int node=1; node<=size; node++) {
      std::ptrdiff_t index = find(visited.begin(), visited.end(), node) - visited.begin();
      // Not found in visited
      if (find(visited.begin(), visited.end(), node) == visited.end()) {
        totalCost += getCost(node);
      }
      else {
        if (index == 0) {
          if (visSize == Dist.getSize()+1) {
            totalCost += Dist.getDist(visited.at(index), visited.at(visSize-2));
            totalCost += Dist.getDist(visited.at(index), visited.at(index+1));
          }
          else {
            totalCost += getCost(visited.at(index), visited.at(index+1));
          }
        }
        else if (index == visSize-1) {
          if (visSize == Dist.getSize()+1) {
            totalCost += Dist.getDist(visited.at(index), visited.at(index-1));
            totalCost += Dist.getDist(visited.at(index), visited.at(0));
          }
          else {
            totalCost += getCost(visited.at(index), visited.at(index-1));
          }
        }
        else {
          totalCost += Dist.getDist(visited.at(index), visited.at(index-1));
          totalCost += Dist.getDist(visited.at(index), visited.at(index+1));
        }
      }
    }
  }
  return totalCost*0.5;
}

void CTMatrix::solve() {
  Path PStart;
  double initialCost = getInitialCost();
  PStart.addNode(1, initialCost);
  CurrentTravelPath.push(PStart);
  bool finished = false;
  while (!finished) {
    Path currentShortestPath = CurrentTravelPath.top();
    std::vector<int> visited = currentShortestPath.getPath();
    finished = CurrentTravelPath.top().getPath().size() == Dist.getSize();
    if (!finished) {
      CurrentTravelPath.pop();
      int size = Dist.getSize();
      for (int dest=1; dest<=size; dest++) {
        if ((Dist.getDist(visited.back(), dest) >= 0) && (find(visited.begin(), visited.end(), dest) == visited.end())) {
          NumCheckedNode += 1;
          std::vector<int> checking = visited;
          checking.push_back(dest);
          Path currentCheckedPath(currentShortestPath);
          double newCost = getNodesCost(checking);
          currentCheckedPath.addNode(dest, newCost);
          CurrentTravelPath.push(currentCheckedPath);
        }
      }
    }
  }
}

Path CTMatrix::getShortestPath() {
  solve();
  Path shortestPath(CurrentTravelPath.top());
  std::vector<int> finalPath = shortestPath.getPath();
  finalPath.push_back(1);
  double finalCost = getNodesCost(finalPath);
  shortestPath.addNode(1, finalCost);

  return shortestPath;
}