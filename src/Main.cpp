// File: Main.cpp
// Author: Rionaldi Chandraseta - 13515077
// Written on 2017-03-31

#include <algorithm>
#include <chrono>
#include <fstream>

#include "Matrix.h"
#include "RCMatrix.h"
#include "CTMatrix.h"

int main() {
  std::chrono::time_point<std::chrono::system_clock> start, end;
  std::string FileName;
  std::cout << "Enter the file name: ";
  std::cin >> FileName;
  std::string extLess = FileName.substr(0, FileName.size()-3);
  std::cout << "Checking files..." << "\n";
  Path shortestPath;
  if ((FileName.at(0) == 'r') && (FileName.at(1) == 'c')) {
    RCMatrix M(FileName);
    std::cout << "Finished loading data" << "\n" << "\n";
    std::cout << "== Travelling Salesman Problem with Reduced Cost Matrix ==" << "\n";
    M.getMatrix().write();
    std::cout << "\n";
    start = std::chrono::system_clock::now();
    shortestPath = M.getShortestPath();
    end = std::chrono::system_clock::now();
    std::cout << "Shortest path: ";
    int numNode = shortestPath.getPath().size();
    for (int i=0; i<numNode; i++) {
      std::cout << shortestPath.getPath().at(i);
      if (i<numNode-1) {
        std::cout << " -> ";
      }
    }
    std::cout << "\n";
    std::cout << "Cost = " << shortestPath.getTotalCost() << "\n";
    std::cout << "Checked " << M.getNumCheckedNode() << " nodes" << "\n";
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout << "Time taken: " << elapsed_seconds.count()*1000 << " ms\n";
    // Output .gv
    std::vector<int> path = shortestPath.getPath();
    Matrix G(FileName);
    path.pop_back();
    std::string fullPath = "../usr/graph_" + extLess + ".gv";
    std::cout << "GraphViz file generated to " << fullPath << "\n";
    std::ofstream oFile;
    oFile.open(fullPath.c_str());
    oFile << "digraph {\n";
    oFile << "\tgraph [layout=circo, overlap=scale, splines=true, mindist=2.5]\n";
    oFile << "\tnode [shape=circle]\n";
    oFile << "\t1 [peripheries=2]\n";
    for (int row=1; row<=G.getSize(); row++) {
      std::ptrdiff_t index = find(path.begin(), path.end(), row) - path.begin();
      for (int col=1; col<=G.getSize(); col++) {
        if (row != col) {
          oFile << "\t" << row << " -> " << col << " [label=" << G.getDist(row, col);
          if (index == path.size()-1) {
            if (path.at(0) == col) {
              oFile << ", color=red, penwidth=3.0, fontcolor=red]\n";
            } else {
              oFile << "]\n";
            }
          } else {
            if (path.at(index+1) == col) {
              oFile << ", color=red, penwidth=3.0, fontcolor=red]\n";
            } else {
              oFile << "]\n";
            }
          }
        }
      }
    }
    oFile << "}";
    oFile.close();
  }
  else if ((FileName.at(0) == 'c') && (FileName.at(1) == 't')) {
    CTMatrix M(FileName);
    std::cout << "Finished loading data" << "\n";
    std::cout << "== Travelling Salesman Problem with Complete Tour ==" << "\n";
    M.getMatrix().write();
    std::cout << "\n";
    start = std::chrono::system_clock::now();
    shortestPath = M.getShortestPath();
    end = std::chrono::system_clock::now();
    std::cout << "Shortest path: ";
    int numNode = shortestPath.getPath().size();
    for (int i=0; i<numNode; i++) {
      std::cout << shortestPath.getPath().at(i);
      if (i<numNode-1) {
        std::cout << " -> ";
      }
    }
    std::cout << "\n";
    std::cout << "Cost = " << shortestPath.getTotalCost() << "\n";
    std::cout << "Checked " << M.getNumCheckedNode() << " nodes" << "\n";
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout << "Time taken: " << elapsed_seconds.count()*1000 << " ms\n";
    // Output .gv
    std::vector<int> path = shortestPath.getPath();
    Matrix G(FileName);
    path.pop_back();
    std::string fullPath = "../usr/graph_" + extLess + ".gv";
    std::cout << "GraphViz file generated to " << fullPath << "\n";
    std::ofstream oFile;
    oFile.open(fullPath);
    oFile << "graph {\n";
    oFile << "\tgraph [layout=circo, overlap=scale, splines=true, mindist=2.5]\n";
    oFile << "\tnode [shape=circle]\n";
    oFile << "\t1 [peripheries=2]\n";
    for (int row=1; row<=G.getSize(); row++) {
      std::ptrdiff_t index = find(path.begin(), path.end(), row) - path.begin();
      for (int col=1; col<row; col++) {
        if (row != col) {
          oFile << "\t" << row << " -- " << col << " [label=" << G.getDist(row, col);
          if (index == path.size()-1) {
            if ((col == path.at(0)) || (col == path.at(index-1))) {
              oFile << ", color=red, penwidth=3.0, fontcolor=red]\n";
            } else {
              oFile << "]\n";
            }
          } else {
            if ((path.at(index+1) == col) || (path.at(index-1) == col)) {
              oFile << ", color=red, penwidth=3.0, fontcolor=red]\n";
            } else {
              oFile << "]\n";
            }
          }
        }
      }
    }
    oFile << "}";
    oFile.close();
  }
  else {
    std::cout << "File not found!" << "\n";
    std::cout << "Exiting program..." << "\n";
  }

  return 0;
}