// File: RCMatrix.cpp
// Author: Rionaldi Chandraseta - 13515077
// Written on 2017-04-01

#include "RCMatrix.h"

RCMatrix::RCMatrix() {}

RCMatrix::RCMatrix(std::string FileName) : Dist(FileName) {
  Bound = 0;
  NumCheckedNode = 1;
}

RCMatrix RCMatrix::createDummy() {
  RCMatrix Dummy;
  Dummy.Dist = Dist;
  Dummy.Bound = Bound;
  Dummy.NumCheckedNode = NumCheckedNode;
  return Dummy;
}

RCMatrix::RCMatrix(const RCMatrix& R) {
  Dist = R.Dist;
  Bound = R.Bound;
  NumCheckedNode = R.NumCheckedNode;
}

Matrix RCMatrix::getMatrix() {
  return Dist;
}

int RCMatrix::getBound() {
  return Bound;
}

int RCMatrix::getNumCheckedNode() {
  return NumCheckedNode;
}

int RCMatrix::lowestRowDist(int row) {
  int min = 0x3f3f3f3f;
  int size = Dist.getSize();
  for (int i=1; i<=size; i++) {
    if ((Dist.getDist(row, i) < min) && (Dist.getDist(row, i) >= 0)) {
      min = Dist.getDist(row, i);
    }
  }
  if (min == 0x3f3f3f3f) {
    min = 0;
  }
  return min;
}

int RCMatrix::lowestColDist(int col) {
  int min = 0x3f3f3f3f;
  int size = Dist.getSize();
  for (int i=1; i<=size; i++) {
    if ((Dist.getDist(i, col) < min) && (Dist.getDist(i, col) >= 0)) {
      min = Dist.getDist(i, col);
    }
  }
  if (min == 0x3f3f3f3f) {
    min = 0;
  }
  return min;
}

void RCMatrix::travel(int orig, int dest) {
  int size = Dist.getSize();
  for (int col=1; col<=size; col++) {
    Dist.setDist(orig, col, INF);
  }
  for (int row=1; row<=size; row++) {
    Dist.setDist(row, dest, INF);
  }
  Dist.setDist(dest, 1, INF);
}

void RCMatrix::reduceMatrix() {
  Bound = 0;
  // Reduce every row
  int size = Dist.getSize();
  for (int row=1; row<=size; row++) {
    int lowDist = lowestRowDist(row);
    for (int col=1; col<=size; col++) {
      if (Dist.getDist(row, col) >= 0) {
        Dist.setDist(row, col, Dist.getDist(row, col) - lowDist);
      }
    }
    Bound += lowDist;
  }
  // Reduce every column
  for (int col=1; col<=size; col++) {
    int lowDist = lowestColDist(col);
    for (int row=1; row<=size; row++) {
      if (Dist.getDist(row, col) >= 0) {
        Dist.setDist(row, col, Dist.getDist(row, col) - lowDist);
      }
    }
    Bound += lowDist;
  }
}

void RCMatrix::solve() {
  reduceMatrix();
  Path PStart;
  PStart.addNode(1, Bound);
  CurrentTravelPath.push(PStart);
  bool finished = false;
  while (!finished) {
    Path currentShortestPath = CurrentTravelPath.top();
    std::vector<int> visited = currentShortestPath.getPath();
    finished = (CurrentTravelPath.top().getPath().size() == Dist.getSize());
    if (!finished) {
      CurrentTravelPath.pop();
      int lastVisited = visited.back();
      RCMatrix AliveNode = createDummy();
      int travelNode = 0;
      while (travelNode < visited.size()) {
        if (travelNode >= 1) {
          AliveNode.travel(visited.at(travelNode-1), visited.at(travelNode));
          if (travelNode < visited.size()-1) {
            AliveNode.reduceMatrix();
          }
        }
        travelNode += 1;
      }
      int size = Dist.getSize();
      for (int dest=1; dest<=size; dest++) {
        if (AliveNode.Dist.getDist(lastVisited, dest) >= 0) {
          NumCheckedNode += 1;
          Path currentCheckedPath(currentShortestPath);
          /////////// DEBUG
          //for (int i=0; i<currentCheckedPath.getPath().size(); i++) {
          // std::cout << currentCheckedPath.getPath().at(i) << " ";
          //}
          //std::cout << dest << std::endl;
          //////////////////
          RCMatrix PossibleNode(AliveNode);
          PossibleNode.reduceMatrix();
          double dist = (double) PossibleNode.Dist.getDist(lastVisited, dest);
          double bound = (double) PossibleNode.getBound();
          //PossibleNode.getMatrix().write();
          //std::cout << "TOTAL DIST BOUND   " << currentCheckedPath.getTotalCost() << " " << dist << " " << bound << std::endl << std::endl;
          currentCheckedPath.addNode(dest, currentCheckedPath.getTotalCost()+dist+bound);
          CurrentTravelPath.push(currentCheckedPath);
        }
      }
    }
  }
}

Path RCMatrix::getShortestPath() {
  solve();
  Path shortestPath(CurrentTravelPath.top());
  shortestPath.addNode(1, shortestPath.getTotalCost());
  return shortestPath;
}