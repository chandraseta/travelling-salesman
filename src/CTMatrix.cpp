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
  for (int row=1; row<=Dist.getSize(); row++) {
    double min = 0x3f3f3f3f;
    double prevMin = 0x3f3f3f3f;
    for (int col=1; col<=Dist.getSize(); col++) {
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
  for (int col=1; col<=Dist.getSize(); col++) {
    if ((col != dest) && (Dist.getDist(orig, col) >= 0) && (Dist.getDist(orig, col) < min)) {
      min = Dist.getDist(orig, col);
    }
  }
  std::cout << "O: " << orig << " D:" << dest << " Min: " << min << std::endl;
  double cost = min + Dist.getDist(orig, dest);
  return cost;
}

double CTMatrix::getCost(int node) {
  double min = 0x3f3f3f3f;
  double prevMin = 0x3f3f3f3f;
  for (int col=1; col<=Dist.getSize(); col++) {
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

double CTMatrix::getNodesCost(std::vector<int> visited, int nextNode) {
  double totalCost = 0;
  if (visited.size()==0) {
    totalCost = 2*getInitialCost();
  }
  else {
    for (int currentNode=1; currentNode<visited.size() ; currentNode++) {
      totalCost += getCost(visited.at(currentNode-1), visited.at(currentNode));
      totalCost += getCost(visited.at(currentNode), nextNode);
    }
    for (int node=1; node<Dist.getSize(); node++) {
      if (find(visited.begin(), visited.end(), node) == visited.end()) {
        totalCost += getCost(node);
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
      for (int dest=1; dest<=Dist.getSize(); dest++) {
        if ((Dist.getDist(visited.back(), dest) >= 0) && (find(visited.begin(), visited.end(), dest) == visited.end())) {
          NumCheckedNode += 1;
          Path currentCheckedPath(currentShortestPath);
          double newCost = getNodesCost(visited, dest);
          currentCheckedPath.addNode(dest, newCost);
          /////////// DEBUG
          for (int i=0; i<currentCheckedPath.getPath().size(); i++) {
           std::cout << currentCheckedPath.getPath().at(i) << " ";
          }
          std::cout << std::endl;
          std::cout << "TOTAL COST = " << newCost << std::endl << std::endl;
          //////////////////
          CurrentTravelPath.push(currentCheckedPath);
        }
      }
    }
  }
}

Path CTMatrix::getShortestPath() {
  solve();
  Path shortestPath(CurrentTravelPath.top());
  shortestPath.addNode(1, shortestPath.getTotalCost());
  return shortestPath;
}