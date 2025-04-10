#ifndef __MATRIX_HPP__ 
#define __MATRIX_HPP__

#include <vector>
#include <iostream>
#include <iomanip>
#include <stdexcept>
using namespace std;

// template class definition with data type T
template <typename T>
class Matrix {
private:
    // store matrix data
    vector<vector<T>> data;
    // N x N matrix size
    size_t size;
public:
    // creates an N x N sized matrix at 0 
    Matrix(size_t N) : size(N), data(N, vector<T>(N, 0)) {}
    // create a matrix from vector data 
    Matrix(const vector<vector<T>>& num) : size(num.size()), data(num) {}
    // addition 
    Matrix operator+(const Matrix &rhs) const {
        // check if sizes match 
        if (size != rhs.size) throw invalid_argument("Error: Matrix sizes do not match (addtion).");
        Matrix result(size);
        // perform addition operation & return result 
        for (size_t i = 0; i < size; ++i)
            for (size_t j = 0; j< size; ++j)
                result.data[i][j] = data[i][j] + rhs.data[i][j];
        return result;
    }
    // multiplication
    Matrix operator*(const Matrix &rhs) const {
        // check if sizes match 
        if (size != rhs.size) throw invalid_argument("Error: Matrix sizes do not match (multiplication).");
        Matrix result(size);
        // perform multiplication operation & return result 
        for (size_t i = 0; i < size; ++i)
            for (size_t j = 0; j < size; ++j)
                for (size_t k = 0; k < size; ++k)
                    result.data[i][j] += data[i][k] * rhs.data[k][j];
        return result;
    }
    // function to set value at specific position
    void setValue(int i, int j, T value) {
        // check if valid 
        if (i < 0 || j < 0 || static_cast<size_t>(i) >= size || static_cast<size_t>(j) >= size)
            throw out_of_range("Error: Indices out of range.");
        data[i][j] = value;
    }
    // function to get value from specific position
    T getValue(int i, int j) const {
        // check if valid 
        if (i < 0 || j < 0 || static_cast<size_t>(i) >= size || static_cast<size_t>(j) >= size)
            throw out_of_range("Error: Indices out of range.");
        return data[i][j];
    }
    // get size of matrix N
    size_t getSize() const {
        return size;
    }
    // function to calculate sum of main diagonal 
    T sumDiagonalMajor() const {
        T sum = 0;
        for (size_t i = 0; i < size; ++i)
            sum += data[i][i];
        return sum;
    }
    // function to calculate sum of minor diagonal 
    T sumDiagonalMinor() const {
        T sum = 0;
        for (size_t i = 0; i < size; ++i)
            sum += data[i][size - 1 - i];
        return sum;
    }
    // function to swap rows
    void swapRows(int r1, int r2) {
        // check if valid 
        if (r1 < 0 || r2 < 0 || static_cast<size_t>(r1) >= size || static_cast<size_t>(r2) >= size)
            throw out_of_range("Error: Row indices out of range.");
        swap(data[r1], data[r2]);
    }
    // function to swap columns 
    void swapCols(int c1, int c2) {
        // check if valid 
        if (c1 < 0 || c2 < 0 || static_cast<size_t>(c1) >= size || static_cast<size_t>(c2) >= size)
            throw out_of_range("Error: Column indices out of range.");
        for (size_t i = 0; i < size; ++i)
            swap(data[i][c1], data[i][c2]);
    }
    // function to print matrix 
    void printMatrix() const {
        for (const auto& row : data) {
            for (const auto& elem : row)
                // set width 
                cout << setw(5) << elem << " ";
            cout << "\n";
        }
    }
};
#endif // __MATRIX_HPP__
