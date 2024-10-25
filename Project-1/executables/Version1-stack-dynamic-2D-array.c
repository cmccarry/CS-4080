#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define MAX_SIZE 100

void inputMatrix(float mat[MAX_SIZE][MAX_SIZE], int *rows, int *cols);
void randomMatrix(float mat[MAX_SIZE][MAX_SIZE], int rows, int cols);
void addMatrices(float mat1[MAX_SIZE][MAX_SIZE], float mat2[MAX_SIZE][MAX_SIZE], float result[MAX_SIZE][MAX_SIZE], int rows, int cols);
void subtractMatrices(float mat1[MAX_SIZE][MAX_SIZE], float mat2[MAX_SIZE][MAX_SIZE], float result[MAX_SIZE][MAX_SIZE], int rows, int cols);
void multiplyMatrices(float mat1[MAX_SIZE][MAX_SIZE], float mat2[MAX_SIZE][MAX_SIZE], float result[MAX_SIZE][MAX_SIZE], int r1, int c1, int c2, long long *duration_ns);
void multiplyMatricesMultipleTimes(float mat1[MAX_SIZE][MAX_SIZE], float mat2[MAX_SIZE][MAX_SIZE], float result[MAX_SIZE][MAX_SIZE], int r1, int c1, int c2, int repetitions);
void printMatrix(float mat[MAX_SIZE][MAX_SIZE], int rows, int cols);
void readMatrixFromFile(float mat[MAX_SIZE][MAX_SIZE], int *rows, int *cols, const char *filename);

// Main Function
int main() {
    int r1 = 0, c1 = 0, r2 = 0, c2 = 0;
    float mat1[MAX_SIZE][MAX_SIZE], mat2[MAX_SIZE][MAX_SIZE], result[MAX_SIZE][MAX_SIZE];
    int choice;
    char filename[100];

    while (1) {
        printf("\nMenu:\n");
        printf("1. Input matrices manually\n");
        printf("2. Generate matrices randomly\n");
        printf("3. Read matrices from file\n");
        printf("4. Add matrices\n");
        printf("5. Subtract matrices\n");
        printf("6. Multiply matrices\n");
        printf("7. Multiply matrices X times and show average time\n");
        printf("8. View both matrices\n");
        printf("9. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);
        printf("\n");

        switch (choice) {
            case 1: // Input manually
                printf("Enter the number of rows and columns for the matrices (max 100x100): ");
                scanf("%d %d", &r1, &c1);
                if (r1 > MAX_SIZE || c1 > MAX_SIZE) {
                    printf("Matrix size exceeds limit.\n");
                    break;
                }
                r2 = r1;
                c2 = c1;
                printf("Enter elements for Matrix 1 (type 'cancel' to stop):\n");
                inputMatrix(mat1, &r1, &c1);
                printf("Enter elements for Matrix 2 (type 'cancel' to stop):\n");
                inputMatrix(mat2, &r2, &c2);
                break;
            case 2: // Generate randomly
                printf("Enter the number of rows and columns for the matrices (max 100x100): ");
                scanf("%d %d", &r1, &c1);
                if (r1 > MAX_SIZE || c1 > MAX_SIZE) {
                    printf("Matrix size exceeds limit.\n");
                    break;
                }
                r2 = r1;
                c2 = c1;
                printf("Randomly generating Matrix 1 and Matrix 2...\n");
                randomMatrix(mat1, r1, c1);
                randomMatrix(mat2, r2, c2);
                break;
            case 3: // Read from file
                printf("Enter filename for Matrix 1: ");
                scanf("%s", filename);
                readMatrixFromFile(mat1, &r1, &c1, filename);
                printf("Enter filename for Matrix 2: ");
                scanf("%s", filename);
                readMatrixFromFile(mat2, &r2, &c2, filename);
                break;
            case 4: // Add matrices
                if (r1 == r2 && c1 == c2) {
                    addMatrices(mat1, mat2, result, r1, c1);
                    printf("Result of addition:\n");
                    printMatrix(result, r1, c1);
                } else {
                    printf("Matrices must have the same dimensions for addition!\n");
                }
                break;
            case 5: // Subtract matrices
                if (r1 == r2 && c1 == c2) {
                    subtractMatrices(mat1, mat2, result, r1, c1);
                    printf("Result of subtraction:\n");
                    printMatrix(result, r1, c1);
                } else {
                    printf("Matrices must have the same dimensions for subtraction!\n");
                }
                break;
            case 6: // Multiply matrices
                if (c1 == r2) {
                    long long duration_ns = 0;
                    multiplyMatrices(mat1, mat2, result, r1, c1, c2, &duration_ns);
                    printf("Result of multiplication:\n");
                    printMatrix(result, r1, c2);
                    printf("Time taken for multiplication (Version 1): %lld nanoseconds\n", duration_ns);
                } else {
                    printf("Matrix 1 columns must equal Matrix 2 rows for multiplication!\n");
                }
                break;
            case 7: // Multiply matrices X times and show average time
                if (c1 == r2) {
                    int repetitions;
                    printf("Enter the number of times to multiply the matrices: ");
                    scanf("%d", &repetitions);
                    multiplyMatricesMultipleTimes(mat1, mat2, result, r1, c1, c2, repetitions);
                } else {
                    printf("Matrix 1 columns must equal Matrix 2 rows for multiplication!\n");
                }
                break;
            case 8: // View both matrices
                printf("Matrix 1:\n");
                printMatrix(mat1, r1, c1);
                printf("Matrix 2:\n");
                printMatrix(mat2, r2, c2);
                break;
            case 9: // Exit
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid option.\n");
                break;
        }
    }
    return 0;
}

// Input matrix manually
void inputMatrix(float mat[MAX_SIZE][MAX_SIZE], int *rows, int *cols) {
    char input[10];
    for (int i = 0; i < *rows; i++) {
        for (int j = 0; j < *cols; j++) {
            printf("Element [%d][%d]: ", i + 1, j + 1);
            scanf("%s", input);
            if (strcmp(input, "cancel") == 0) {
                printf("Input cancelled. Returning to menu.\n");
                return;
            }
            mat[i][j] = atof(input);
        }
    }
}

// Random matrix generation
void randomMatrix(float mat[MAX_SIZE][MAX_SIZE], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            mat[i][j] = ((float)(rand() % 10000)) / 100.0;
        }
    }
}

// Addition of matrices
void addMatrices(float mat1[MAX_SIZE][MAX_SIZE], float mat2[MAX_SIZE][MAX_SIZE], float result[MAX_SIZE][MAX_SIZE], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[i][j] = mat1[i][j] + mat2[i][j];
        }
    }
}

// Subtraction of matrices
void subtractMatrices(float mat1[MAX_SIZE][MAX_SIZE], float mat2[MAX_SIZE][MAX_SIZE], float result[MAX_SIZE][MAX_SIZE], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[i][j] = mat1[i][j] - mat2[i][j];
        }
    }
}

// Matrix multiplication
void multiplyMatrices(float mat1[MAX_SIZE][MAX_SIZE], float mat2[MAX_SIZE][MAX_SIZE], float result[MAX_SIZE][MAX_SIZE], int r1, int c1, int c2, long long *duration_ns) {
    LARGE_INTEGER frequency, start, end;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start);

    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c2; j++) {
            result[i][j] = 0;
            for (int k = 0; k < c1; k++) {
                result[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }
    QueryPerformanceCounter(&end);

    *duration_ns = (end.QuadPart - start.QuadPart) * 1000000000LL / frequency.QuadPart;
}

// Matrix multiplication X times and show average time
void multiplyMatricesMultipleTimes(float mat1[MAX_SIZE][MAX_SIZE], float mat2[MAX_SIZE][MAX_SIZE], float result[MAX_SIZE][MAX_SIZE], int r1, int c1, int c2, int repetitions) {
    LARGE_INTEGER frequency, start, end;
    long long total_duration_ns = 0;

    QueryPerformanceFrequency(&frequency);

    for (int rep = 0; rep < repetitions; rep++) {
        QueryPerformanceCounter(&start);

        for (int i = 0; i < r1; i++) {
            for (int j = 0; j < c2; j++) {
                result[i][j] = 0;
                for (int k = 0; k < c1; k++) {
                    result[i][j] += mat1[i][k] * mat2[k][j];
                }
            }
        }
        QueryPerformanceCounter(&end);
        total_duration_ns += (end.QuadPart - start.QuadPart) * 1000000000LL / frequency.QuadPart;
    }
    long long average_duration_ns = total_duration_ns / repetitions;
    printf("Average time for %d matrix multiplications (Version 1): %lld nanoseconds\n", repetitions, average_duration_ns);
}

// Print matrix
void printMatrix(float mat[MAX_SIZE][MAX_SIZE], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%.2f ", mat[i][j]);
        }
        printf("\n");
    }
}

// Read matrix from file
void readMatrixFromFile(float mat[MAX_SIZE][MAX_SIZE], int *rows, int *cols, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("File not found!\n");
        return;
    }
    fscanf(file, "%d %d", rows, cols);
    for (int i = 0; i < *rows; i++) {
        for (int j = 0; j < *cols; j++) {
            fscanf(file, "%f", &mat[i][j]);
        }
    }
    fclose(file);
}
