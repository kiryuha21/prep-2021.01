#include "matrix.h"
#include "exceptions.h"

namespace prep {
    Matrix::Matrix(size_t rows, size_t cols): cols(cols), rows(rows) {
        this->matrix_content.resize(rows);
        for (size_t i = 0; i < rows; ++i) {
            this->matrix_content[i].resize(cols);
        }
    }

    Matrix::Matrix(std::istream& is) {
        is >> this->rows >> this->cols;
        this->matrix_content.resize(this->rows);
        for (size_t i = 0; i < this->rows; ++i) {
            this->matrix_content[i].resize(this->cols);
            for (size_t j = 0; j < this->cols; ++j) {
                is >> this->matrix_content[i][j];
            }
        }
    }

    size_t Matrix::getRows() const {
        return this->rows;
    }

    size_t Matrix::getCols() const {
        return this->cols;
    }

    double Matrix::operator()(size_t i, size_t j) const {
        return this->matrix_content[i][j];
    }

    double& Matrix::operator()(size_t i, size_t j) {
        return this->matrix_content[i][j];
    }

    std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {
        for (size_t i = 0; i < matrix.rows; ++i) {
            for (size_t j = 0; j < matrix.cols; ++j) {
                os << matrix(i, j);
            }
        }
        return os;
    }

    bool Matrix::operator==(const Matrix &rhs) const {
        if (this->rows != rhs.rows || this->cols != rhs.cols) {
            return false;
        }
        for (size_t i = 0; i < this->rows; ++i) {
            for (size_t j = 0; j < this->cols; ++j) {
                if (this->matrix_content[i][j] != rhs.matrix_content[i][j]) {
                    return false;
                }
            }
        }
        return true;
    }
    
    bool Matrix::operator!=(const Matrix &rhs) const {
        return !(*this == rhs);
    }

    Matrix Matrix::operator+(const Matrix &rhs) const {
        Matrix temp(this->rows, this->cols);
        for (size_t i = 0; i < this->getCols(); ++i) {
            for (size_t j = 0; j < this->getRows(); ++j) {
                temp.matrix_content[i][j] = this->matrix_content[i][j] + rhs.matrix_content[i][j];
            }
        }
        return temp;
    }
    
    Matrix Matrix::operator-(const Matrix &rhs) const {
        Matrix temp(this->rows, this->cols);
        for (size_t i = 0; i < this->getCols(); ++i) {
            for (size_t j = 0; j < this->getRows(); ++j) {
                temp.matrix_content[i][j] = this->matrix_content[i][j] - rhs.matrix_content[i][j];
            }
        }
        return temp;
    }

    Matrix Matrix::operator*(const Matrix &rhs) const {
        Matrix temp(this->rows, rhs.cols);
        for (size_t i = 0; i < this->rows; ++i) {
            for (size_t j = 0; j < rhs.cols; ++j) {
                temp.matrix_content[i][j]= 0;
                for (size_t k = 0; k < this->cols; ++k)
                    temp.matrix_content[i][j] += this->matrix_content[i][k] * rhs.matrix_content[k][j];
            }
        }
        return temp;
    }

    Matrix Matrix::operator*(double val) const {
        Matrix temp(this->rows, this->cols);
        for (size_t i = 0; i < this->rows; ++i) {
            for (size_t j = 0; j < this->cols; ++j) {
                temp.matrix_content[i][j] = this->matrix_content[i][j] * val;
            }
        }
        return temp;
    }

    Matrix operator*(double val, const Matrix& matrix) {
        Matrix temp(matrix.rows, matrix.cols);
        for (size_t i = 0; i < matrix.rows; ++i) {
            for (size_t j = 0; j < matrix.cols; ++j) {
                temp.matrix_content[i][j] = matrix.matrix_content[i][j] * val;
            }
        }
        return temp;
    }

    Matrix Matrix::transp() const {
        Matrix temp(this->cols, this->rows);
        for (size_t i = 0; i < this->cols; ++i) {
            for (size_t j = 0; j < this->rows; ++j) {
                temp.matrix_content[i][j] = this->matrix_content[j][i];
            }
        }
        return temp;
    }

    void minus_row_col(std::vector<std::vector<double>> origin_matrix, std::vector<std::vector<double>> temp_matrix, size_t row, size_t col) {
        size_t miss_row = 0;

        for (size_t i = 0; i < origin_matrix.size() - 1; ++i) {
            if (i == row) {
                miss_row = 1;
            }
            size_t miss_col = 0;
            for (size_t j = 0; j < origin_matrix.size() - 1; ++j) {
                if (j == col) {
                    miss_col = 1;
                }
                temp_matrix[i][j] = origin_matrix[i + miss_row][j + miss_col];
            }
        }
    }

    double recursive_det(std::vector<std::vector<double>> origin_matrix) { //Исключения!!
        double temp_det = 0;

        if (origin_matrix.size() == 1) {
            temp_det = origin_matrix[0][0];
            return(temp_det);
        }

        if (origin_matrix.size() == 2) {
            temp_det = origin_matrix[0][0] * origin_matrix[1][1] - (origin_matrix[1][0] * origin_matrix[0][1]);
            return(temp_det);
        }

        std::vector<std::vector<double>> temp_matrix;
        temp_matrix.resize(origin_matrix.size() - 1);
        for (size_t i = 0; i < origin_matrix.size() - 1; ++i) {
            temp_matrix[i].resize(origin_matrix.size() -1);
        }

        int sign = 1;
        for (size_t i = 0; i < origin_matrix.size(); ++i) {
            minus_row_col(origin_matrix, temp_matrix, i, 0);
            temp_det = temp_det + sign * origin_matrix[i][0] * recursive_det(temp_matrix);
            sign = -sign;
        }
        return temp_det;
    }

    double Matrix::det() const {
        return recursive_det(this->matrix_content);
    }

    Matrix Matrix::adj() const {
        Matrix temp_matrix(this->rows, this->cols);
        int sign = 1;

        for (size_t i = 0; i < temp_matrix.rows; ++i) {
            for (size_t j = 0; j < temp_matrix.cols; ++j) {
                Matrix additions_matrix(temp_matrix.rows - 1, temp_matrix.cols - 1);
                minus_row_col(this->matrix_content, additions_matrix.matrix_content, j, i);
                if ((i + j) % 2 == 0) {
                    sign = 1;
                } else {
                    sign = -1;
                }
                temp_matrix.matrix_content[i][j] = sign * recursive_det(additions_matrix.matrix_content);
            }
        }
        return temp_matrix;
    }


    Matrix Matrix::inv() const{
        if (this->cols == 1) {
            Matrix temp_matrix(1, 1);
            temp_matrix.matrix_content[0][0] = 1 / this->matrix_content[0][0];
            return temp_matrix;
        }

        Matrix adj_temp = adj();
        Matrix temp_matrix = adj_temp * (1 / recursive_det(this->matrix_content));
        return temp_matrix;
    }


}
