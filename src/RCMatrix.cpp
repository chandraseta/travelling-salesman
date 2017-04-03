// File: RCMatrix.cpp
// Author: Rionaldi Chandraseta - 13515077
// Written on 2017-04-01

#include <algorithm>

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

RCMatrix RCMatrix::createCopy(const RCMatrix& R) {
  RCMatrix Copy;
  Copy.Dist = R.Dist;
  Copy.Bound = R.Bound;
  Copy.NumCheckedNode = R.NumCheckedNode;
  return Copy;
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
  for (int i=1; i<=Dist.getSize(); i++) {
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
  for (int i=1; i<=Dist.getSize(); i++) {
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
  for (int col=1; col<=Dist.getSize(); col++) {
    Dist.setDist(orig, col, INF);
  }
  for (int row=1; row<=Dist.getSize(); row++) {
    Dist.setDist(row, dest, INF);
  }
  Dist.setDist(dest, 1, INF);
}

void RCMatrix::reduceMatrix() {
  Bound = 0;
  // Reduce every row
  for (int row=1; row<=Dist.getSize(); row++) {
    int lowDist = lowestRowDist(row);
    for (int col=1; col<=Dist.getSize(); col++) {
      if (Dist.getDist(row, col) >= 0) {
        Dist.setDist(row, col, Dist.getDist(row, col) - lowDist);
      }
    }
    Bound += lowDist;
  }
  // Reduce every column
  for (int col=1; col<=Dist.getSize(); col++) {
    int lowDist = lowestColDist(col);
    for (int row=1; row<=Dist.getSize(); row++) {
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
    CurrentTravelPath.pop();
    int lastVisited = visited.back();
    RCMatrix AliveNode = createDummy();
    int travelNode = 0;
    while (travelNode < visited.size()) {
      if (travelNode >= 1) {
        AliveNode.travel(visited.at(travelNode-1), visited.at(travelNode));
        AliveNode.reduceMatrix();
      }
      travelNode += 1;
    }
    for (int dest=1; dest<=Dist.getSize(); dest++) {
      if (AliveNode.Dist.getDist(lastVisited, dest) >= 0) {
        NumCheckedNode += 1;
        Path currentCheckedPath = currentShortestPath;
        RCMatrix PossibleNode = createCopy(AliveNode);
        PossibleNode.reduceMatrix();
        int dist = PossibleNode.Dist.getDist(lastVisited, dest);
        int bound = PossibleNode.getBound();
        std::cout << currentCheckedPath.getTotalCost() << " " << dist << " " << bound << std::endl;
        currentCheckedPath.addNode(dest, currentCheckedPath.getTotalCost()+dist+bound);
        CurrentTravelPath.push(currentCheckedPath);
      }
    }
    finished = (CurrentTravelPath.top().getPath().size() == Dist.getSize());
  }
}

std::priority_queue<Path, std::vector<Path>, ComparePath> RCMatrix::getShortestPath() {
  solve();
  return CurrentTravelPath;
}