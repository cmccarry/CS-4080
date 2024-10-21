#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 100

void inputMatrix(float mat[MAX_SIZE][MAX_SIZE], int rows, int cols);
void randomMatrix(float mat[MAX_SIZE][MAX_SIZE], int rows, int cols);
void addMatrices(float mat1[MAX_SIZE][MAX_SIZE], float mat2[MAX_SIZE][MAX_SIZE], float result[MAX_SIZE][MAX_SIZE], int rows, int cols);
void subtractMatrices(float mat1[MAX_SIZE][MAX_SIZE], float mat2[MAX_SIZE][MAX_SIZE], float result[MAX_SIZE][MAX_SIZE], int rows, int cols);
void multiplyMatrices(float mat1[MAX_SIZE][MAX_SIZE], float mat2[MAX_SIZE][MAX_SIZE], float result[MAX_SIZE][MAX_SIZE], int r1, int c1, int c2);
void printMatrix(float mat[MAX_SIZE][MAX_SIZE], int rows, int cols);
void readMatrixFromFile(float mat[MAX_SIZE][MAX_SIZE], int *rows, int *cols, const char *filename);

int main() {
    int r1, c1, r2, c2;
    float mat1[MAX_SIZE][MAX_SIZE], mat2[MAX_SIZE][MAX_SIZE], result[MAX_SIZE][MAX_SIZE];
    int choice;
    char filename[100];

    printf("Enter the number of rows and columns for Matrix 1 (max 100x100): ");
    scanf("%d %d", &r1, &c1);
    printf("Enter the number of rows and columns for Matrix 2 (max 100x100): ");
    scanf("%d %d", &r2, &c2);

    if (r1 > MAX_SIZE || c1 > MAX_SIZE || r2 > MAX_SIZE || c2 > MAX_SIZE) {
        printf("Matrix sizes exceed the limit.\n");
        return -1;
    }

    while (1) {
        printf("\nMenu:\n");
        printf("1. Input matrices manually\n");
        printf("2. Generate matrices randomly\n");
        printf("3. Read matrices from file\n");
        printf("4. Add matrices\n");
        printf("5. Subtract matrices\n");
        printf("6. Multiply matrices\n");
        printf("7. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter elements for Matrix 1:\n");
                inputMatrix(mat1, r1, c1);
                printf("Enter elements for Matrix 2:\n");
                inputMatrix(mat2, r2, c2);
                break;
            case 2:
                printf("Randomly generating Matrix 1 and Matrix 2...\n");
                randomMatrix(mat1, r1, c1);
                randomMatrix(mat2, r2, c2);
                break;
            case 3:
                printf("Enter filename for Matrix 1: ");
                scanf("%s", filename);
                readMatrixFromFile(mat1, &r1, &c1, filename);
                printf("Enter filename for Matrix 2: ");
                scanf("%s", filename);
                readMatrixFromFile(mat2, &r2, &c2, filename);
                break;
            case 4:
                if (r1 == r2 && c1 == c2) {
                    addMatrices(mat1, mat2, result, r1, c1);
                    printf("Result of addition:\n");
                    printMatrix(result, r1, c1);
                } else {
                    printf("Matrices must have the same dimensions for addition!\n");
                }
                break;
            case 5:
                if (r1 == r2 && c1 == c2) {
                    subtractMatrices(mat1, mat2, result, r1, c1);
                    printf("Result of subtraction:\n");
                    printMatrix(result, r1, c1);
                } else {
                    printf("Matrices must have the same dimensions for subtraction!\n");
                }
                break;
            case 6:
                if (c1 == r2) {
                    clock_t start = clock();
                    multiplyMatrices(mat1, mat2, result, r1, c1, c2);
                    clock_t end = clock();
                    printf("Result of multiplication:\n");
                    printMatrix(result, r1, c2);
                    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
                    printf("Time taken for multiplication: %f seconds\n", time_taken);
                } else {
                    printf("Matrix 1 columns must equal Matrix 2 rows for multiplication!\n");
                }
                break;
            case 7:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid option.\n");
                break;
        }
    }
    return 0;
}

void inputMatrix(float mat[MAX_SIZE][MAX_SIZE], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("Element [%d][%d]: ", i + 1, j + 1);
            scanf("%f", &mat[i][j]);
        }
    }
}

void randomMatrix(float mat[MAX_SIZE][MAX_SIZE], int rows, int cols) {
    srand(time(0));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            mat[i][j] = (float)(rand() % 100) / 10;
        }
    }
}

void addMatrices(float mat1[MAX_SIZE][MAX_SIZE], float mat2[MAX_SIZE][MAX_SIZE], float result[MAX_SIZE][MAX_SIZE], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[i][j] = mat1[i][j] + mat2[i][j];
        }
    }
}

void subtractMatrices(float mat1[MAX_SIZE][MAX_SIZE], float mat2[MAX_SIZE][MAX_SIZE], float result[MAX_SIZE][MAX_SIZE], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[i][j] = mat1[i][j] - mat2[i][j];
        }
    }
}

void multiplyMatrices(float mat1[MAX_SIZE][MAX_SIZE], float mat2[MAX_SIZE][MAX_SIZE], float result[MAX_SIZE][MAX_SIZE], int r1, int c1, int c2) {
    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c2; j++) {
            result[i][j] = 0;
            for (int k = 0; k < c1; k++) {
                result[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }
}

void printMatrix(float mat[MAX_SIZE][MAX_SIZE], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%f ", mat[i][j]);
        }
        printf("\n");
    }
}

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
