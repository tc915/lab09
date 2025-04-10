#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdexcept>
#include <numeric> 
#include <algorithm>

template <typename T>
class Matrix {
private:
    int N; // size of the square matrix (N x N)
    std::vector<std::vector<T>> data;

public:
    // constructor
    Matrix(int size) : N(size) {
        if (size <= 0) {
            throw std::invalid_argument("Matrix size must be positive.");
        }
        // init data vector with N rows, each having N columns
        data.resize(N, std::vector<T>(N));
    }

    // problem 1: load matrix data from an input stream
    void load(std::ifstream& ifs) {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (!(ifs >> data[i][j])) {
                    throw std::runtime_error("Error reading matrix data from file or not enough data.");
                }
            }
        }
    }

    // problem 1: display matrix
    void display() const {
        // width for alignment
        const int fieldWidth = 8;
        std::cout << std::fixed << std::setprecision(2); // print as double with 2 decimal places

        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                // cast to double
                std::cout << std::setw(fieldWidth) << static_cast<double>(data[i][j]);
            }
            std::cout << std::endl;
        }
        std::cout << std::endl; // add a blank line after the matrix
    }

    // getter for size
    int getSize() const {
        return N;
    }

    // accessor for elements (const version)
    const T& getElement(int r, int c) const {
        if (r < 0 || r >= N || c < 0 || c >= N) {
            throw std::out_of_range("Matrix index out of bounds.");
        }
        return data[r][c];
    }

    // accessor for elements (non-const version)
    T& getElement(int r, int c) {
        if (r < 0 || r >= N || c < 0 || c >= N) {
            throw std::out_of_range("Matrix index out of bounds.");
        }
        return data[r][c];
    }


    // problem 2: add two matrices (operator overloading)
    Matrix<T> operator+(const Matrix<T>& other) const {
        if (this->N != other.N) {
            throw std::invalid_argument("Matrices must have the same dimensions for addition.");
        }
        Matrix<T> result(N);
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                result.data[i][j] = this->data[i][j] + other.data[i][j];
            }
        }
        return result;
    }

    // problem 3: multiply two matrices (Operator Overloading)
    Matrix<T> operator*(const Matrix<T>& other) const {
        if (this->N != other.N) {
            throw std::invalid_argument("Matrices must have the same dimensions for multiplication.");
        }
        Matrix<T> result(N); // init result matrix with zeros
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                T sum = T(); // init sum for the element to zero
                for (int k = 0; k < N; ++k) {
                    sum += this->data[i][k] * other.data[k][j];
                }
                result.data[i][j] = sum;
            }
        }
        return result;
    }

    // problem 4: get the sum of matrix diagonal elements
    T getDiagonalSum() const {
        T mainDiagSum = T();
        T secondaryDiagSum = T();
        for (int i = 0; i < N; ++i) {
            mainDiagSum += data[i][i];
            secondaryDiagSum += data[i][N - 1 - i];
        }
        T totalSum = mainDiagSum + secondaryDiagSum;
        if (N % 2 != 0) {
            totalSum -= data[N / 2][N / 2];
        }
        return totalSum;
    }

    // problem 5: swap matrix rows
    void swapRows(int r1, int r2) {
        if (r1 < 0 || r1 >= N || r2 < 0 || r2 >= N) {
            std::cerr << "Warning: Row index out of bounds for swapping. No swap performed." << std::endl;
            return;
        }
        if (r1 == r2) return;
        std::swap(data[r1], data[r2]);
    }

    // problem 6: swap matrix columns
    void swapCols(int c1, int c2) {
         if (c1 < 0 || c1 >= N || c2 < 0 || c2 >= N) {
            std::cerr << "Warning: Column index out of bounds for swapping. No swap performed." << std::endl;
            return;
        }
        if (c1 == c2) return;
        for (int i = 0; i < N; ++i) {
            std::swap(data[i][c1], data[i][c2]);
        }
    }

    // problem 7: update matrix element
    void updateElement(int r, int c, T value) {
        if (r < 0 || r >= N || c < 0 || c >= N) {
             std::cerr << "Warning: Index out of bounds for update. No update performed." << std::endl;
            return;
        }
        data[r][c] = value;
    }
};

#endif