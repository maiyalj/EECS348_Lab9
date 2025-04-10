#include "matrix.hpp"
#include <fstream>
#include <sstream>
using namespace std;

// template function to read from file 
template <typename T>
Matrix<T> readMatrix(const string& filename, bool second = false) {
    // open file
    ifstream file(filename);
    // error handling 
    if (!file.is_open())
        throw runtime_error("Error: Unable to open file.");
    // read matrix size N
    size_t N;
    file >> N;
    // initialize structure 
    vector<vector<T>> matrixData(N, vector<T>(N));
    // determine which matrix to read from 
    if (second) {
        // skip first elements and read next N x N elements 
        T temp;
        for (size_t i = 0; i < 2 * N * N; ++i) {
            file >> temp;
            if (i >= N * N)
                matrixData[(i - N * N) / N][(i - N * N) % N] = temp; 
        }
    // read N x N elements 
    } else {
        for (size_t i = 0; i < N; ++i)
            for (size_t j = 0; j < N; ++j)
                file >> matrixData[i][j];
    }
    // return constructed object from data 
    return Matrix<T>(matrixData);
}
// main function 
int main(int argc, char* argv[]) {
    string filename;
    // get filename from user 
    if (argc == 2) {
        filename = argv[1];
    } else {
        cout << "Enter filename: ";
        cin >> filename;
    }
    try {
        // read from file 
        Matrix<int> A = readMatrix<int>(filename, false);
        Matrix<int> B = readMatrix<int>(filename, true);
        // print originals 
        cout << "Matrix A:\n";
        A.printMatrix();
        cout << "\nMatrix B:\n";
        B.printMatrix();
        // print matrix sum
        cout << "\nA + B:\n";
        (A + B).printMatrix();
        // print matrix product 
        cout << "\nA * B:\n";
        (A * B).printMatrix();
        // print major and minor diagonal sums 
        cout << "\nMain Diagonal of A: " << A.sumDiagonalMajor();
        cout << "\nMinor Diagonal of A: " << A.sumDiagonalMinor() << "\n";
        // swap rows
        cout << "\nSwap rows 0 & 1:\n";
        A.swapRows(0, 1);
        A.printMatrix();
        // swap columns 
        cout << "\nSwap columns 0 & 1:\n";
        A.swapCols(0, 1);
        A.printMatrix();
        // set a value 
        cout << "Update (0, 0) to 99:\n";
        A.setValue(0, 0, 99);
        A.printMatrix();
    } catch (const exception& e) {
        // error handling 
        cerr << "Error: " << e.what() << "\n";
        return 1;
    }
    return 0;
}
