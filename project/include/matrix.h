#pragma once

#include <vector>
#include <iostream>
#include <iomanip>
#include <limits>

namespace prep {
class Matrix {
 private:
    size_t cols, rows;
    std::vector<std::vector<double>> matrix_content;
    static bool is_empty(std::istream& matrix_file);
    static double recursive_det(const Matrix& origin_matrix);
    static void minus_row_col(const Matrix& origin_matrix, Matrix& temp_matrix, size_t row, size_t col);

 public:
    explicit Matrix(size_t rows = 0, size_t cols = 0);
    explicit Matrix(std::istream& is);
    Matrix(const Matrix& rhs) = default;
    Matrix& operator=(const Matrix& rhs) = default;
    ~Matrix() = default;

    size_t getRows() const;
    size_t getCols() const;

    double operator()(size_t i, size_t j) const;
    double& operator()(size_t i, size_t j);

    bool operator==(const Matrix& rhs) const;
    bool operator!=(const Matrix& rhs) const;

    Matrix operator+(const Matrix& rhs) const;
    Matrix operator-(const Matrix& rhs) const;
    Matrix operator*(const Matrix& rhs) const;

    Matrix operator*(double val) const;

    friend Matrix operator*(double val, const Matrix& matrix);
    friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix);

    Matrix transp() const;
    double det() const;
    Matrix adj() const;
    Matrix inv() const;
};

Matrix operator*(double val, const Matrix& matrix);
std::ostream& operator<<(std::ostream& os, const Matrix& matrix);
}  // namespace prep