#include "matrix.h"
#include <ctime>
#include <iostream>

int main(){
  matrix m1(512);
  size_t start = clock();
  matrix mi = m1.inverse(10);
  std::cout << static_cast<double>(clock() - start) / CLOCKS_PER_SEC << std::endl;
  return 0;
}