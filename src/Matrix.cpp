// File: Matrix.cpp
// Author: Rionaldi Chandraseta - 13515077
// Written on 2017-03-31

#include "Matrix.h"

Matrix::Matrix() {}

Matrix::Matrix(std::string FileName) {
  // FileName must be validated before calling the constructor.
  std::ifstream File(FileName);
  std::string Str;
  getline(File, Str);

  int SpaceCount = 0;
  int Idx = 0;
  while (Idx < Str.length()) {
    if (Str.at(Idx) == ' ') {
      SpaceCount += 1;
    }
    Idx += 1;
  }
  MSize = SpaceCount + 1;

  Mem = new int* [MSize+1];
  for (int i=0; i<=(MSize); i++) {
    Mem[i] = new int [MSize+1];
  }

  // Read from beginning of file
  File.clear();
  File.seekg(0, std::ios::beg);

  // INDEXING starts from 1 to prevent disorientation
  int row = 1;
  while (!File.eof()) {
    for (int col=1; col<=MSize; col++) {
      File >> Mem[row][col];
    }
    row += 1;
  }

  File.close();
}

Matrix::Matrix(const Matrix& M) {
  MSize = M.MSize;
  Mem = new int* [MSize+1];
  for (int i=0; i<=(MSize); i++) {
    Mem[i] = new int [MSize+1];
  }

  for (int row=1; row<=MSize; row++) {
    for (int col=1; col<=MSize; col++) {
      Mem[row][col] = M.Mem[row][col];
    }
  }
}

Matrix::~Matrix() {
  for (int i=0; i<=MSize; i++) {
    delete [] Mem[i];
  }
  delete [] Mem;
}

Matrix& Matrix::operator=(const Matrix& M) {
  MSize = M.MSize;
  Mem = new int* [MSize+1];
  for (int i=0; i<=(MSize); i++) {
    Mem[i] = new int [MSize+1];
  }

  for (int row=1; row<=MSize; row++) {
    for (int col=1; col<=MSize; col++) {
      Mem[row][col] = M.Mem[row][col];
    }
  }
  return *this;
}

int Matrix::getDist(int ori, int dest) {
  return Mem[ori][dest];
}

void Matrix::setDist(int ori, int dest, int dist) {
  Mem[ori][dest] = dist;
}

int Matrix::getSize() {
  return MSize;
}

void Matrix::write() {
  for (int row=1; row<=MSize; row++) {
    for (int col=1; col<=MSize; col++) {
      if (Mem[row][col] == -1) {
        std::cout << " inf";
      }
      else{
        if (Mem[row][col] < 10) {
          std::cout << "   ";
        }
        else {
          std::cout << "  ";
        }
        std::cout << Mem[row][col];
      }
    }
    std::cout << std::endl;
  }
}