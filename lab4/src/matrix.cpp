#include "matrix.h"
#include <cmath>
#include <cstring>


matrix::matrix() {
  _size = 0;
  _matrix = nullptr;
}

matrix::matrix(const size_t size) {
  _size = size;
  _matrix = new float[_size * _size];
  memset(_matrix, 0, _size * _size * sizeof(float));
  for(size_t i = 0; i < _size; ++i){
    _matrix[i*_size + i] = 1;
  }
}

matrix::matrix(const matrix& other) {
  auto* tmp = new float[other._size * other._size];
  for(size_t i = 0; i < other._size; ++i){
    for(size_t j = 0; j < other._size; ++j){
      tmp[i*other._size + j] = other._matrix[i*other._size + j];
    }
  }
  _size = other._size;
  _matrix = tmp;
}

matrix& matrix::operator=(const matrix &other) {
  auto* tmp = new float[other._size * other._size];
  for(size_t i = 0; i < other._size; ++i){
    for(size_t j = 0; j < other._size; ++j){
      tmp[i*other._size + j] = other._matrix[i*other._size + j];
    }
  }
  delete[] _matrix;
  _size = other._size;
  _matrix = tmp;
  return *this;
}

void matrix::fill(const size_t row, const size_t column) {
  _matrix[row*_size + column] = 1;
}

matrix matrix::transpose() const{
  matrix transpose(_size);
  for(size_t i = 0; i < _size; ++i){
    for(size_t j = 0; j < _size; ++j){
      transpose._matrix[i*_size + j] = _matrix[j*_size + i];
    }
  }
  return transpose;
}

<<<<<<< HEAD
matrix& matrix::operator+=(const matrix& other) {
=======
matrix& matrix::inverse() {

}

matrix& matrix::operator+(const matrix& other) {
>>>>>>> 9f76e9cf1a9028a1f70d6c54b455c0683dffe95a
  if(_size != other._size){
    std::cout << "not allowed" << std::endl;
  }
  for(size_t i = 0; i < _size; ++i){
    for(size_t j = 0; j < _size; ++j){
      _matrix[i*_size + j] += other._matrix[i*other._size + j];
    }
  }
  return *this;
}

matrix& matrix::operator-=(const matrix& other){
  if(_size != other._size){
    std::cout << "not allowed" << std::endl;
  }
  for(size_t i = 0; i < _size; ++i){
    for(size_t j = 0; j < _size; ++j){
      _matrix[i*_size + j] -= other._matrix[i*other._size + j];
    }
  }
  return *this;
}

matrix& matrix::operator*=(const matrix& other){
  auto* tmp = new float[_size * other._size];
  memset(tmp, 0, other._size * other._size * sizeof(float));
  for(size_t i = 0; i < _size; ++i){
    for(size_t j = 0; j < other._size; ++j){
      for(size_t k = 0; k < _size; ++k){
        tmp[i*_size + j] += _matrix[i*_size + k] * other._matrix[k*other._size + j];
      }
    }
  }
  delete[] _matrix;
  _matrix = tmp;
  return *this;
}

matrix& matrix::operator*=(const float scalar){
  for(size_t i = 0; i < _size; ++i){
    for(size_t j = 0; j < _size; ++j){
      _matrix[j*_size + i] *= scalar;
    }
  }
  return *this;
}

matrix operator+(const matrix& other1, const matrix& other2) {
  matrix tmp(other1);
  return (tmp += other2);
}

matrix operator-(const matrix& other1, const matrix& other2) {
  matrix tmp(other1);
  return (tmp -= other2);
}

matrix operator*(const matrix& other1, const matrix& other2) {
  matrix tmp(other1);
  return (tmp *= other2);
}

matrix operator*(const matrix& other, float scalar) {
  matrix tmp(other);
  return (tmp *= scalar);
}

float matrix::max_row() const{
  float max = 0;
  for(size_t i = 0; i < _size; ++i){
    float current = 0;
    for(size_t j = 0; j < _size; ++j){
      current += std::fabs(_matrix[i*_size + j]);
    }
    if(current > max) max = current;
  }
  return max;
}

float matrix::max_collumn() const{
  return (*this).transpose().max_row();
}

matrix matrix::inverse(const size_t M) const {
  matrix tmp(*this);
  matrix I(_size);
  matrix B = tmp.transpose() * (1.0f / (tmp.max_collumn() * tmp.max_row()));
  matrix R = I - (B * (*this));
  tmp = I;
  for (size_t i = 0; i < M; ++i) {
    tmp = tmp + R;
    R = R * R;
  }
  tmp = tmp * B;
  return tmp;
}


void matrix::print() const{
  for(size_t i = 0; i < _size; ++i){
    for(size_t j = 0; j < _size; ++j){
      std::cout << _matrix[i*_size + j] << " ";
    }
    std::cout << std::endl;
  }
}

matrix::~matrix(){
  delete[] _matrix;
}
