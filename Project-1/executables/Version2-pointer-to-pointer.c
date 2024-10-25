#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define MAX_SIZE 100

void inputMatrix(float ***mat, int *rows, int *cols);
void randomMatrix(float ***mat, int rows, int cols);
void addMatrices(float **mat1, float **mat2, float **result, int rows, int cols);
void subtractMatrices(float **mat1, float **mat2, float **result, int rows, int cols);
float **multiplyMatrices(float **mat1, float **mat2, int r1, int c1, int c2, long long *duration_ns);
void multiplyMatricesMultipleTimes(float **mat1, float **mat2, int r1, int c1, int c2, int repetitions);
void printMatrix(float **mat, int rows, int cols);
void freeMatrix(float **mat, int rows);
void readMatrixFromFile(float ***mat, int *rows, int *cols, const char *filename);

// Main Function
int main() {
    int r1 = 0, c1 = 0, r2 = 0, c2 = 0;
    float **mat1 = NULL, **mat2 = NULL, **result = NULL;
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
                printf("Enter elements for Matrix 1:\n");
                inputMatrix(&mat1, &r1, &c1);
                printf("Enter elements for Matrix 2:\n");
                inputMatrix(&mat2, &r2, &c2);
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
                randomMatrix(&mat1, r1, c1);
                randomMatrix(&mat2, r2, c2);
                break;
            case 3: // Read from file
                printf("Enter filename for Matrix 1: ");
                scanf("%s", filename);
                readMatrixFromFile(&mat1, &r1, &c1, filename);
                printf("Enter filename for Matrix 2: ");
                scanf("%s", filename);
                readMatrixFromFile(&mat2, &r2, &c2, filename);
                break;
            case 4: // Add matrices
                if (r1 == r2 && c1 == c2) {
                    result = (float **)malloc(r1 * sizeof(float *));
                    for (int i = 0; i < r1; i++) {
                        result[i] = (float *)malloc(c1 * sizeof(float));
                    }
                    addMatrices(mat1, mat2, result, r1, c1);
                    printf("Result of addition:\n");
                    printMatrix(result, r1, c1);
                    freeMatrix(result, r1);
                } else {
                    printf("Matrices must have the same dimensions for addition!\n");
                }
                break;
            case 5: // Subtract matrices
                if (r1 == r2 && c1 == c2) {
                    result = (float **)malloc(r1 * sizeof(float *));
                    for (int i = 0; i < r1; i++) {
                        result[i] = (float *)malloc(c1 * sizeof(float));
                    }
                    subtractMatrices(mat1, mat2, result, r1, c1);
                    printf("Result of subtraction:\n");
                    printMatrix(result, r1, c1);
                    freeMatrix(result, r1);
                } else {
                    printf("Matrices must have the same dimensions for subtraction!\n");
                }
                break;
            case 6: // Multiply matrices
                if (c1 == r2) {
                    long long duration_ns = 0;
                    result = multiplyMatrices(mat1, mat2, r1, c1, c2, &duration_ns);
                    printf("Result of multiplication:\n");
                    printMatrix(result, r1, c2);
                    printf("Time taken for multiplication (Version 2): %lld nanoseconds\n", duration_ns);
                    freeMatrix(result, r1);
                } else {
                    printf("Matrix 1 columns must equal Matrix 2 rows for multiplication!\n");
                }
                break;
            case 7: // Multiply matrices X times and show average time
                if (c1 == r2) {
                    int repetitions;
                    printf("Enter the number of times to multiply the matrices: ");
                    scanf("%d", &repetitions);
                    multiplyMatricesMultipleTimes(mat1, mat2, r1, c1, c2, repetitions);
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
                freeMatrix(mat1, r1);
                freeMatrix(mat2, r2);
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid option.\n");
                break;
        }
    }
    return 0;
}

// Input matrix
void inputMatrix(float ***mat, int *rows, int *cols) {
    *mat = (float **)malloc(*rows * sizeof(float *));
    for (int i = 0; i < *rows; i++) {
        (*mat)[i] = (float *)malloc(*cols * sizeof(float));
        for (int j = 0; j < *cols; j++) {
            printf("Element [%d][%d]: ", i + 1, j + 1);
            scanf("%f", &(*mat)[i][j]);
        }
    }
}

// Generate random matrix
void randomMatrix(float ***mat, int rows, int cols) {
    *mat = (float **)malloc(rows * sizeof(float *));
    for (int i = 0; i < rows; i++) {
        (*mat)[i] = (float *)malloc(cols * sizeof(float));
        for (int j = 0; j < cols; j++) {
            (*mat)[i][j] = ((float)(rand() % 10000)) / 100.0;
        }
    }
}

// Add matrices
void addMatrices(float **mat1, float **mat2, float **result, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[i][j] = mat1[i][j] + mat2[i][j];
        }
    }
}

// Subtract matrices
void subtractMatrices(float **mat1, float **mat2, float **result, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[i][j] = mat1[i][j] - mat2[i][j];
        }
    }
}

// Multiply matrices
float **multiplyMatrices(float **mat1, float **mat2, int r1, int c1, int c2, long long *duration_ns) {
    LARGE_INTEGER frequency, start, end;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start);

    // Allocate result matrix
    float **result = (float **)malloc(r1 * sizeof(float *));
    for (int i = 0; i < r1; i++) {
        result[i] = (float *)malloc(c2 * sizeof(float));
        for (int j = 0; j < c2; j++) {
            result[i][j] = 0;
            for (int k = 0; k < c1; k++) {
                result[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }
    QueryPerformanceCounter(&end);
    *duration_ns = (end.QuadPart - start.QuadPart) * 1000000000LL / frequency.QuadPart;

    return result;
}

// Multiply matrices X times and show average time
void multiplyMatricesMultipleTimes(float **mat1, float **mat2, int r1, int c1, int c2, int repetitions) {
    LARGE_INTEGER frequency, start, end;
    long long total_duration_ns = 0;

    QueryPerformanceFrequency(&frequency);

    // Allocate result matrix (temporary, won't be used)
    float **result = (float **)malloc(r1 * sizeof(float *));
    for (int i = 0; i < r1; i++) {
        result[i] = (float *)malloc(c2 * sizeof(float));
    }

    // Perform the matrix multiplication `repetitions` times
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

    printf("Average time for %d matrix multiplications (Version 2): %lld nanoseconds\n", repetitions, average_duration_ns);
    // Free result matrix
    freeMatrix(result, r1);
}

// Free dynamically allocated matrix
void freeMatrix(float **mat, int rows) {
    for (int i = 0; i < rows; i++) {
        free(mat[i]);
    }
    free(mat);
}

// Print matrix
void printMatrix(float **mat, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%.2f ", mat[i][j]);
        }
        printf("\n");
    }
}

// Read matrix from file
void readMatrixFromFile(float ***mat, int *rows, int *cols, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("File not found!\n");
        return;
    }
    fscanf(file, "%d %d", rows, cols);
    *mat = (float **)malloc(*rows * sizeof(float *));
    for (int i = 0; i < *rows; i++) {
        (*mat)[i] = (float *)malloc(*cols * sizeof(float));
        for (int j = 0; j < *cols; j++) {
            fscanf(file, "%f", &(*mat)[i][j]);
        }
    }
    fclose(file);
}