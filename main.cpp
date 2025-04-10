#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>
#include "matrix.h"

// template function to process both int and double matrices
template <typename T>
void processMatrices(std::ifstream& ifs, int N) {
    try {
        // create matrices
        Matrix<T> matrixA(N);
        Matrix<T> matrixB(N);

        // problem 1: load and display
        std::cout << "Loading Matrix A..." << std::endl;
        matrixA.load(ifs);
        std::cout << "Loading Matrix B..." << std::endl;
        matrixB.load(ifs);

        std::cout << "\nProblem 1: Display Matrices" << std::endl;
        std::cout << "Matrix A:" << std::endl;
        matrixA.display();
        std::cout << "Matrix B:" << std::endl;
        matrixB.display();

        // problem 2: add matrices
        std::cout << "Problem 2: Matrix Addition (A + B)" << std::endl;
        Matrix<T> sum = matrixA + matrixB;
        std::cout << "Result:" << std::endl;
        sum.display();

        // problem 3: multiply matrices
        std::cout << "Problem 3: Matrix Multiplication (A * B)" << std::endl;
        Matrix<T> product = matrixA * matrixB;
        std::cout << "Result:" << std::endl;
        product.display();

        // problem 4: diagonal sum
        std::cout << "Problem 4: Diagonal Sum of Matrix A" << std::endl;
        T diagSumA = matrixA.getDiagonalSum();
        // display as double
        std::cout << "Sum of main and secondary diagonals: "
                  << static_cast<double>(diagSumA) << std::endl << std::endl;

        // problem 5: swap rows
        int row1_to_swap = 0;
        int row2_to_swap = 1; // example rows
         if (N > 1) { // only swap if there's more than one row
            std::cout << "Problem 5: Swap Rows " << row1_to_swap << " and " << row2_to_swap << " in Matrix A" << std::endl;
            std::cout << "Matrix A before row swap:" << std::endl;
            matrixA.display();
            matrixA.swapRows(row1_to_swap, row2_to_swap);
            std::cout << "Matrix A after row swap:" << std::endl;
            matrixA.display();
        } else {
             std::cout << "Problem 5: Swap Rows" << std::endl;
             std::cout << "Matrix size is 1, skipping row swap" << std::endl << std::endl;
        }


        // problem 6: swap columns
        int col1_to_swap = 1;
        int col2_to_swap = 2; // example columns
        if (N > 2) { // only swap if there are enough columns
             std::cout << "Problem 6: Swap Columns " << col1_to_swap << " and " << col2_to_swap << " in Matrix A" << std::endl;
             std::cout << "Matrix A before column swap:" << std::endl;
             matrixA.display();
             matrixA.swapCols(col1_to_swap, col2_to_swap);
             std::cout << "Matrix A after column swap:" << std::endl;
             matrixA.display();
        } else {
            std::cout << "Problem 6: Swap Columns" << std::endl;
            std::cout << "Matrix size is too small, skipping column swap example" << std::endl << std::endl;
        }

        // problem 7:update element
        int row_to_update = 0;
        int col_to_update = 0;
        T new_value = static_cast<T>(99); // example update
        std::cout << "Problem 7: Update Element (" << row_to_update << ", " << col_to_update
                  << ") in Matrix A to " << static_cast<double>(new_value) << "" << std::endl;
        std::cout << "Matrix A before update:" << std::endl;
        matrixA.display();
        matrixA.updateElement(row_to_update, col_to_update, new_value);
        std::cout << "Matrix A after update:" << std::endl;
        matrixA.display();

    } catch (const std::exception& e) {
        std::cerr << "Error during matrix processing: " << e.what() << std::endl;
    }
}

int main(int argc, char* argv[]) {
    std::string filename;

    if (argc < 2) {
        std::cout << "Please enter the input filename: ";
        std::cin >> filename;
    } else {
        filename = argv[1];
    }

    std::ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        std::cerr << "Error: Could not open file '" << filename << "'" << std::endl;
        return 1;
    }

    int N;
    int type_flag;

    // read matrix size (N) and type flag from the first line
    if (!(inputFile >> N >> type_flag)) {
        std::cerr << "Error: Could not read matrix size and type flag from file." << std::endl;
        inputFile.close();
        return 1;
    }

    if (N <= 0) {
         std::cerr << "Error: Invalid matrix size N = " << N << " read from file." << std::endl;
         inputFile.close();
         return 1;
    }

    std::cout << "Matrix size (N): " << N << std::endl;
    std::cout << "Matrix type flag: " << type_flag << (type_flag == 0 ? " (int)" : " (double)") << std::endl;
    std::cout << "----------------------------------------" << std::endl;


    // branch based on the type flag
    if (type_flag == 0) { // integer matrices
        processMatrices<int>(inputFile, N);
    } else if (type_flag == 1) { // double matrices
        processMatrices<double>(inputFile, N);
    } else {
        std::cerr << "Error: Invalid type flag '" << type_flag << "'. Use 0 for int or 1 for double." << std::endl;
        inputFile.close();
        return 1;
    }

    inputFile.close();
    return 0;
}