#ifndef LAB4
#define LAB4

#include <iostream>

class matrix{
 public:
  matrix();
  explicit matrix(size_t size);
  matrix(const matrix& other);

  matrix& operator=(const matrix& other);

  void fill(size_t row, size_t column);

  matrix& transposition();

  matrix& operator+(const matrix& other);
  matrix& operator-(const matrix& other);

  matrix& operator*(const matrix& other);
  matrix& operator*(float scalar);

  void print();

  ~matrix();

 private:
  size_t _size;
  float* _matrix;
};

#endif //LAB4
