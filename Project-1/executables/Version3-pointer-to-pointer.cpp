#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <stdexcept>
#include <chrono>
#include <fstream>

#define MAX_SIZE 100

class Matrix {
private:
    float **data;
    int rows, cols;

    // Helper function to allocate memory
    void allocateMemory() {
        data = new float*[rows];
        for (int i = 0; i < rows; i++) {
            data[i] = new float[cols];
        }
    }

public:
    // Constructor: Initialize matrix
    Matrix(int r, int c) : rows(r), cols(c) {
        allocateMemory();
    }

    // Destructor: Free allocated memory
    ~Matrix() {
        for (int i = 0; i < rows; i++) {
            delete[] data[i];
        }
        delete[] data;
    }

    // Copy Constructor
    Matrix(const Matrix &other) : rows(other.rows), cols(other.cols) {
        allocateMemory();
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                data[i][j] = other.data[i][j];
            }
        }
    }

    // Overloaded Assignment Operator
    Matrix& operator=(const Matrix &other) {
        if (this == &other) return *this;  // Self-assignment check
        for (int i = 0; i < rows; i++) {
            delete[] data[i];
        }
        delete[] data;

        rows = other.rows;
        cols = other.cols;
        allocateMemory();

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                data[i][j] = other.data[i][j];
            }
        }
        return *this;
    }

    // Function to input matrix data
    void inputMatrix() {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                std::cout << "Element [" << i + 1 << "][" << j + 1 << "]: ";
                std::cin >> data[i][j];
            }
        }
    }

    // Function to randomly generate matrix data
    void randomMatrix() {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                data[i][j] = static_cast<float>(rand() % 10000) / 100.0;
            }
        }
    }

    // Function to read matrix data from a file
    void readFromFile(const std::string &filename) {
        std::ifstream file(filename);
        if (!file) {
            throw std::runtime_error("Error opening file.");
        }
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                file >> data[i][j];
            }
        }
        file.close();
    }

    // Overloaded operator for matrix addition (+)
    Matrix operator+(const Matrix &other) const {
        if (rows != other.rows || cols != other.cols) {
            throw std::invalid_argument("Matrix dimensions must match for addition.");
        }
        Matrix result(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result.data[i][j] = data[i][j] + other.data[i][j];
            }
        }
        return result;
    }

    // Overloaded operator for matrix subtraction (-)
    Matrix operator-(const Matrix &other) const {
        if (rows != other.rows || cols != other.cols) {
            throw std::invalid_argument("Matrix dimensions must match for subtraction.");
        }
        Matrix result(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result.data[i][j] = data[i][j] - other.data[i][j];
            }
        }
        return result;
    }

    // Overloaded operator for matrix multiplication (*)
    Matrix operator*(const Matrix &other) const {
        if (cols != other.rows) {
            throw std::invalid_argument("Matrix dimensions must be compatible for multiplication.");
        }
        Matrix result(rows, other.cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < other.cols; j++) {
                result.data[i][j] = 0;
                for (int k = 0; k < cols; k++) {
                    result.data[i][j] += data[i][k] * other.data[k][j];
                }
            }
        }
        return result;
    }

    // Function to display matrix data
    void printMatrix() const {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                std::cout << std::setw(8) << std::fixed << std::setprecision(2) << data[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
};

// Function to display the menu
void displayMenu() {
    std::cout << "\nMenu:\n";
    std::cout << "1. Input matrices manually\n";
    std::cout << "2. Generate matrices randomly\n";
    std::cout << "3. Read matrices from file\n";
    std::cout << "4. Add matrices\n";
    std::cout << "5. Subtract matrices\n";
    std::cout << "6. Multiply matrices\n";
    std::cout << "7. View both matrices\n";
    std::cout << "8. Multiply matrices X times and show average time\n";
    std::cout << "9. Exit\n";
    std::cout << "Choose an option: ";
}

// Function to multiply matrices multiple times and show the average time
void multiplyMatricesMultipleTimes(const Matrix &mat1, const Matrix &mat2, int repetitions) {
    using namespace std::chrono;

    long long total_duration_ns = 0;

    for (int i = 0; i < repetitions; i++) {
        auto start = high_resolution_clock::now();
        Matrix result = mat1 * mat2;
        auto end = high_resolution_clock::now();
        total_duration_ns += duration_cast<nanoseconds>(end - start).count();
    }

    long long average_duration_ns = total_duration_ns / repetitions;

    std::cout << "Average time for " << repetitions << " matrix multiplications: (Version 3)" << average_duration_ns << " nanoseconds\n";
}

int main() {
    int r1 = 0, c1 = 0, r2 = 0, c2 = 0;
    Matrix *mat1 = nullptr, *mat2 = nullptr;
    int choice;

    while (true) {
        displayMenu();
        std::cin >> choice;

        switch (choice) {
            case 1: // Input matrices manually
                std::cout << "Enter rows and columns for Matrix 1: ";
                std::cin >> r1 >> c1;
                mat1 = new Matrix(r1, c1);
                std::cout << "Enter elements for Matrix 1:\n";
                mat1->inputMatrix();

                std::cout << "Enter rows and columns for Matrix 2: ";
                std::cin >> r2 >> c2;
                mat2 = new Matrix(r2, c2);
                std::cout << "Enter elements for Matrix 2:\n";
                mat2->inputMatrix();
                break;

            case 2: // Generate matrices randomly
                std::cout << "Enter rows and columns for Matrix 1: ";
                std::cin >> r1 >> c1;
                mat1 = new Matrix(r1, c1);
                mat1->randomMatrix();

                std::cout << "Enter rows and columns for Matrix 2: ";
                std::cin >> r2 >> c2;
                mat2 = new Matrix(r2, c2);
                mat2->randomMatrix();
                break;

            case 3: // Read matrices from file
                std::cout << "Enter rows and columns for Matrix 1: ";
                std::cin >> r1 >> c1;
                mat1 = new Matrix(r1, c1);
                std::cout << "Enter filename for Matrix 1: ";
                {
                    std::string filename;
                    std::cin >> filename;
                    mat1->readFromFile(filename);
                }

                std::cout << "Enter rows and columns for Matrix 2: ";
                std::cin >> r2 >> c2;
                mat2 = new Matrix(r2, c2);
                std::cout << "Enter filename for Matrix 2: ";
                {
                    std::string filename;
                    std::cin >> filename;
                    mat2->readFromFile(filename);
                }
                break;

            case 4: // Add matrices
                if (mat1 && mat2 && r1 == r2 && c1 == c2) {
                    Matrix result_add = *mat1 + *mat2;
                    std::cout << "Result of Matrix 1 + Matrix 2:\n";
                    result_add.printMatrix();
                } else {
                    std::cout << "Matrices must have the same dimensions for addition!\n";
                }
                break;

            case 5: // Subtract matrices
                if (mat1 && mat2 && r1 == r2 && c1 == c2) {
                    Matrix result_sub = *mat1 - *mat2;
                    std::cout << "Result of Matrix 1 - Matrix 2:\n";
                    result_sub.printMatrix();
                } else {
                    std::cout << "Matrices must have the same dimensions for subtraction!\n";
                }
                break;

            case 6: // Multiply matrices
                if (mat1 && mat2 && c1 == r2) {
                    auto start = std::chrono::high_resolution_clock::now();
                    Matrix result_mul = *mat1 * *mat2;
                    auto end = std::chrono::high_resolution_clock::now();
                    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

                    std::cout << "Result of Matrix 1 * Matrix 2:\n";
                    result_mul.printMatrix();
                    std::cout << "Time taken for multiplication: (Version 3)" << duration << " nanoseconds\n";
                } else {
                    std::cout << "Matrix 1 columns must equal Matrix 2 rows for multiplication!\n";
                }
                break;

            case 7: // View both matrices
                if (mat1 && mat2) {
                    std::cout << "Matrix 1:\n";
                    mat1->printMatrix();
                    std::cout << "Matrix 2:\n";
                    mat2->printMatrix();
                } else {
                    std::cout << "Matrices are not initialized.\n";
                }
                break;

            case 8: // Multiply matrices X times and show average time
                if (mat1 && mat2 && c1 == r2) {
                    int repetitions;
                    std::cout << "Enter the number of repetitions: ";
                    std::cin >> repetitions;
                    multiplyMatricesMultipleTimes(*mat1, *mat2, repetitions);
                } else {
                    std::cout << "Matrix 1 columns must equal Matrix 2 rows for multiplication!\n";
                }
                break;

            case 9: // Exit
                std::cout << "Exiting...\n";
                delete mat1;
                delete mat2;
                return 0;

            default:
                std::cout << "Invalid option.\n";
                break;
        }
    }

    return 0;
}