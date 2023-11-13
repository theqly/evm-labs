#include "matrix.h"
#include <iostream>

int main(){
  std::cout << "matrix" << std::endl;
  matrix mt1(5);

  mt1.print();

  mt1.fill(0, 2);
  mt1.fill(0, 4);
  mt1.fill(2, 3);
  mt1.fill(4, 1);
  std::cout << std::endl;

  mt1.print();

  matrix mt2(mt1);
  mt1.transposition();
  std::cout << std::endl;

  mt1.print();

  matrix mt3 = mt1 + mt2;
  std::cout << std::endl;
  mt3.print();
  return 0;
}