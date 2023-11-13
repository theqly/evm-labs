#include <cstring>
#include "matrix.h"

matrix::matrix() {
  _size = 0;
  _matrix = nullptr;
}

matrix::matrix(size_t size) {
  _size = size;
  _matrix = new float[_size * _size];
  memset(_matrix, 0, _size * _size * sizeof(float));
}

matrix::matrix(const matrix& other) {
  auto tmp = new float[other._size * other._size];
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

void matrix::fill(size_t row, size_t column) {
  _matrix[row*_size + column] = 1;
}

matrix& matrix::transposition() {
  auto* tmp = new float[_size * _size];
  for(size_t i = 0; i < _size; ++i){
    for(size_t j = 0; j < _size; ++j){
      tmp[i*_size + j] = _matrix[j*_size + i];
    }
  }
  delete[] _matrix;
  _matrix = tmp;
  return *this;
}

matrix& matrix::operator+(const matrix& other) {
  if(_size != other._size){
    std::cout << "not allowed" << std::endl;
  }
  auto* tmp = new float[_size * _size];
  for(size_t i = 0; i < _size; ++i){
    for(size_t j = 0; j < _size; ++j){
      tmp[i*_size + j] = _matrix[i*_size + j] + other._matrix[i*other._size + j];
    }
  }
  delete[] _matrix;
  _matrix = tmp;
  return *this;
}

matrix& matrix::operator-(const matrix& other){
  if(_size != other._size){
    std::cout << "not allowed" << std::endl;
  }
  auto* tmp = new float[_size * _size];
  for(size_t i = 0; i < _size; ++i){
    for(size_t j = 0; j < _size; ++j){
      tmp[i*_size + j] = _matrix[i*_size + j] - other._matrix[i*other._size + j];
    }
  }
  delete[] _matrix;
  _matrix = tmp;
  return *this;
}

matrix& matrix::operator*(const matrix& other){
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

matrix& matrix::operator*(float scalar){
  auto tmp = new float[_size * _size];
  for(size_t i = 0; i < _size; ++i){
    for(size_t j = 0; j < _size; ++j){
      tmp[i*_size + j] = _matrix[j*_size + i] * scalar;
    }
  }
  delete[] _matrix;
  _matrix = tmp;
  return *this;
}

void matrix::print() {
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
