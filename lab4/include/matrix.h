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

<<<<<<< HEAD
    [[nodiscard]] matrix transpose() const;
=======
  matrix& transposition();
  matrix& inverse();
>>>>>>> 9f76e9cf1a9028a1f70d6c54b455c0683dffe95a

    matrix& operator+=(const matrix& other);
    matrix& operator-=(const matrix& other);
    matrix& operator*=(const matrix& other);
    matrix& operator*=(float scalar);

    friend matrix operator+(const matrix& other1, const matrix& other2);
    friend matrix operator-(const matrix& other1, const matrix& other2);
    friend matrix operator*(const matrix& other1, const matrix& other2);
    friend matrix operator*(const matrix& other, float scalar);

    [[nodiscard]] float max_collumn() const;
    [[nodiscard]] float max_row() const;

    matrix inverse(size_t M) const;

    void print() const;

    ~matrix();

  private:
    size_t _size;
    float* _matrix;
};

#endif //LAB4
