// File: Main.cpp
// Author: Rionaldi Chandraseta - 13515077
// Written on 2017-03-31

#include "Matrix.h"
#include "RCMatrix.h"
#include "CTMatrix.h"

int main() {
  std::string FileName;
  std::cout << "Enter the file name: ";
  std::cin >> FileName;
  std::cout << "Checking files..." << std::endl;
  if ((FileName.compare("data1.in") == 0) || (FileName.compare("data2.in") == 0)) {
    std::cout << "Finished loading data" << std::endl << std::endl;
    std::cout << "Travelling Salesman Problem with Reduced Cost Matrix" << std::endl;
    RCMatrix M(FileName);
    M.getMatrix().write();
    Path shortestPath = M.getShortestPath();
    int numNode = shortestPath.getPath().size();
    for (int i=0; i<numNode; i++) {
      std::cout << shortestPath.getPath().at(i) << " ";
    }
    std::cout << std::endl;
    std::cout << "Cost = " << shortestPath.getTotalCost() << std::endl;
    std::cout << "Checked " << M.getNumCheckedNode() << " nodes" << std::endl;
  }
  else if ((FileName.compare("data3.in") == 0) || (FileName.compare("data4.in") == 0)) {
    std::cout << "Finished loading data" << std::endl;
    std::cout << "Travelling Salesman Problem with Complete Tour" << std::endl;
    CTMatrix M(FileName);
    M.getMatrix().write();
    Path shortestPath = M.getShortestPath();
    int numNode = shortestPath.getPath().size();
    for (int i=0; i<numNode; i++) {
      std::cout << shortestPath.getPath().at(i) << " ";
    }
    std::cout << std::endl;
    std::cout << "Cost = " << shortestPath.getTotalCost() << std::endl;
    std::cout << "Checked " << M.getNumCheckedNode() << " nodes" << std::endl;
  }
  else {
    std::cout << "File not found!" << std::endl;
    std::cout << "Exiting program..." << std::endl;
  }

  return 0;
}